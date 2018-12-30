# jemalloc 분석



## 목표 

다음을 이해하고 찾는다. 

- 알고리즘 
- 구현 기법
- 사용법 
- 개선
- 활용



## 자료

- http://jemalloc.net/
  - jemalloc의 문서
  - 위키 
  - 논문과 presentation

- https://github.com/jemalloc/jemalloc
  - 소스 



## 코드 

jemalloc release 5.1.0을 받다. msvc 폴더에 jemalloc_vc2017.sln으로 시작. 



파일 목록: 

- arena.c
- background_thread.c
- base.c
- bin.c
- bitmap.c
- ckh.c
- ctl.c
- div.c
- extent.c
- extent_dss.c
- extent_mmap.c
- hash.c
- hooks.c
- jemalloc.c
- large.c
- log.c
- malloc_io.c
- mutex.c
- mutex_pool.c
- nstime.c
- pages.c
- prng.c
- prof.c
- rtee.c
- stats.c
- sz.c
- tcache.c
- ticker.c
- tsd.c
- witness.c

31개 파일들. 헤더는 include에 따로 있다. 파일 개수가 많지 않으나 여러 가지 배워야 할 개념이 있다. 

개념, 기법, 구현, 활용으로 나아간다. 어떤 임계점을 넘어 확고하게 이해해야 한다. 





## 개요

```
jemalloc is a general purpose malloc(3) implementation that emphasizes fragmentation avoidance and scalable concurrency support. jemalloc first came into use as the FreeBSD libc allocator in 2005, and since then it has found its way into numerous applications that rely on its predictable behavior. In 2010 jemalloc development efforts broadened to include developer support features such as heap profiling and extensive monitoring/tuning hooks. Modern jemalloc releases continue to be integrated back into FreeBSD, and therefore versatility remains critical. Ongoing development efforts trend toward making jemalloc among the best allocators for a broad range of demanding applications, and eliminating/mitigating weaknesses that have practical repercussions for real world applications.
```

단편화를 줄이고 동시성을 올리는 일반적인 용도의 malloc 구현이다. FreeBSD의 libc allocator로 2005년 쓰였다. 2010년 힙 프로파일링과 광범위한 모니터링 / 튜닝 기능을 추가했다. FreeBSD에 계속 통합되고 되어 여러 곳에 쓰일 수 있어야 하고 실질적인 응용에 방해가 되는 약점을 제거하거나 줄일 수 있어야 한다. 

일반적인 malloc이면서 동시에 OS에서 사용 가능할 정도로 쉬워야 하고 실제 응용 프로그램에서 사용했을 때 약점이 없어야 하거나 영향이 거의 없어야 한다. 

이런 목표를 달성하기는 쉽지 않다. 모든 애플리케이션을 만족시키는 동시성이 뛰어나면서 동시에 단편화를 줄이는 메모리 관리기에다가 메모리 사용량이나 필요한 모니터링 기능을 갖추고 있어야 하기 때문이다. 

### 비디오 

https://www.youtube.com/watch?v=RcWp5vwGlYU&feature=youtu.be&list=PLn0nrSd4xjjZoaFwsTnmS1UFj3ob7gf7s

http://applicative.acm.org/2015/applicative.acm.org/speaker-JasonEvans.html

- histroy
  - experimental language runtime
  - freebsd
  - firefox
  - facebook operations
    - introspection
- malloc in a nutshell
  - malloc / calloc / realloc / free 
- jemalloc features
  - scalable 
  - low fragmentation 
  - degenerate behavior unlikely
  - APIS: 
    - *allocx 
    - mallctrl*

- Terminology 
  - Arena
    - Chunk : 1024 contiguous pages (4MiB)
      - Page run 
        - Region 
  - Unused dirty page
- Arena chunks
- Internal / external fragmentation
  - internal : per allocation 
- Fragmentation avoidance
  - prefer low addresses during reuse
  - stable ordering works: proof? 



stops here... 



## Core Algorithms and Data Structures

https://www.facebook.com/notes/facebook-engineering/scalable-memory-allocation-using-jemalloc/480222803919



- Segregate small objects according to size class, and prefer low addresses during re-use. phkmalloc에서 유래. 
- Carefully choose size classes (Inspired by Vam). 
- Impose tight limits on allocator metadata overhead.
- Minimize the active page set. 
- Minimize lock contention. lkmalloc에서 유래. arena 단위. tcmalloc에서 TLS 형식 사용. 따라서, jemalloc도 이를 따름. 
- If it isn't general purpose, it isn't good enough. 단편화에 대한 올바른 접근은 jemalloc의 레이아웃 알고리즘을 단순하게 만들어 성능과 예측성을 올린 것이다. 이런 접근이 약점을 개선하는 올바른 관점이다. (특수한 경우를 추가하지 않고 일반적인 해결책을 만든다)



세 가지 크기 분류가 있다. 

- Small: [8], [16, 32, 48, ..., 128], [192, 256, 320, ..., 512], [768, 1024, 1280, 3840]
- Large: [4 KiB, 8 KiB, ..., 4072 KiB]
- Huge: [4 MiB, 8 MiB, 12 MiB, ... ]

![jemalloc_arena](img\jemalloc_arena.jpg)

arena chunk는 서로 완전히 분리되어 있다. 

```
Each arena chunk contains metadata (primarily a page map), followed by one or more page runs. Small objects are grouped together, with additional metadata at the start of each page run, whereas large objects are independent of each other, and their metadata reside entirely in the arena chunk header. Each arena tracks non-full small object page runs via red-black trees (one for each size class), and always services allocation requests using the non-full run with the lowest address for that size class. Each arena tracks available page runs via two red-black trees — one for clean/untouched page runs, and one for dirty/touched page runs. Page runs are preferentially allocated from the dirty tree, using lowest best fit.
```

소스 볼 때 이 부분이 알고리즘의 핵심이므로 꼼꼼히 살핀다. 

![je_malloc_arena_thread_layout](img\je_malloc_arena_thread_layout.jpg)



```
Each thread maintains a cache of small objects, as well as large objects up to a limited size (32 KiB by default). Thus, the vast majority of allocation requests first check for a cached available object before accessing an arena. Allocation via a thread cache requires no locking whatsoever, whereas allocation via an arena requires locking an arena bin (one per small size class) and/or the arena as a whole.

The main goal of thread caches is to reduce the volume of synchronization events. Therefore, the maximum number of cached objects for each size class is capped at a level that allows for a 10-100X synchronization reduction in practice. Higher caching limits would further speed up allocation for some applications, but at an unacceptable fragmentation cost in the general case. To further limit fragmentation, thread caches perform incremental "garbage collection" (GC), where time is measured in terms of allocation requests. Cached objects that go unused for one or more GC passes are progressively flushed to their respective arenas using an exponential decay approach.
```

- thread cache 
- GC w/ exponential decay 



## Facebook Motivated Innovations

자랑이긴 하나 이후 많이 좋아진 건 맞다. tcmalloc과 경쟁한다. 

### Speed

- thread caching
  - simple design of data structures
    - singly linked LIFO for each size class
  - size control 
    - hard limit for each size class 
    - incremental GC completely independent of other threads
- increased mutex granularity 
  - restructured dirty page purging facilities to drop all mutexes before calling madvise(). 
- reworte dirty page purging. 
- developed a new red-black tree implementation
  - red-black tree의 세부 구현 변경
  - non-recursive left-leaning 2-3 red-black tree 



### Introspection 

- mallctl*() API 
  - malloc_stats_print() 
- heap profiling 
  - leak detection

jemalloc is more active than tcmalloc. 



## malloc_stats_print 

애플리케이션에서 사용하는 메모리 전체를 트래킹 가능하게 만들려고 한다. 

jemalloc은 어떻게 구현했는 지 본다. 









































