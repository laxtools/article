# WPF Programming 

사람들에게 유용한 프로그램이 되려면 UI가 필요하다. GUI로 예쁘고 쓰기 편하면 더욱 좋다. GUI는 요즘 webkit을 사용한 electron 등이 대세이다. 하지만 반응성이 아직은 좀 떨어지는 면이 있다. WPF는 필요한 도구를 개발하는데 유용하며 xaml 기반으로 웹 기술을 많이 수용하고 있어 이해하고 있다면 작고 큰 도구의 개발과 GUI 전체를 이해하는데 도움이 많이 된다. 따라서, WPF와 electron 두 가지를 모두 익힌다. 

여기서는 튜토리얼 중심으로 진행한다. 찰스 페졸드의 WPF 책이 있어 가끔 참조하도록 한다. 좀 내용이 많아 요즘 스타일이라고 보기는 어렵지만 뛰어나신 분이고 25년 전 윈도우즈 프로그래밍의 핵심을 정리하신 분이다. 

# 개요 

https://wpf-tutorial.com/getting-started/hello-wpf/

검색 처음에 나오는 튜토리얼이다. 160여개 아티클이라고 한다. 프로그래밍을 이해하고 있고 GUI의 내부 구현도 알고 있으므로 WPF을 익히는데 집중한다. GUI는 구조의 이해보다는 아트 측면의 세심한 훈련이 필요하다. 바둑처럼 규칙은 단순하나 수는 많은 게임이다. 



# Hello WPF

WPF는 DirectX 기반의 렌더링을 사용한다. 성능도 뛰어날 뿐만 아니라 렌더링 품질이 매우 좋다. GUI 렌더링은 이미지와 텍스트이 깔끔해야 전체적으로 예뻐 보인다. 그런 면에서 WPF는 좋다. 

xaml은 UI를 정의한다. 모든 게임은 event, action, state, effect로 이루어진다. 따라서, xaml은 action / effect와 state를 정의한다. event도 정의할 수 있을 것으로 보인다. 



# What is XAML 

## Basic XAML 

```xaml
<Button>
    <Button.FontWeight>Bold</Button.FontWeight>
    <Button.Content>A button</Button.Content>
</Button>
```

또는 

```xaml
<Button FontWeight="Bold" Content="A button" />
```

좀 더 복잡하고 완전한 예시다.

```xaml
<Button>
    <Button.FontWeight>Bold</Button.FontWeight>
    <Button.Content>
        <WrapPanel>
            <TextBlock Foreground="Blue">Multi</TextBlock>
            <TextBlock Foreground="Red">Color</TextBlock>
            <TextBlock>Button</TextBlock>
        </WrapPanel>
    </Button.Content>
</Button>
```

GUI는 레이아웃이 중요한 상태이다. 또 속성을 지정해야 한다. 이들을 기억하고 익숙하게 사용하는 것이 가장 중요한 훈련이다. 그전에는 개념만 이해하면 넘어갔다. 그건 프로그래머의 자세가 아니다. 프로그래머는 사람들이 사용할 수 있는 도구를 만들 때 해당 기능을 안다고 할 수 있다. 

xaml의 기능은 실행하는 코드가 있으므로 당연히 코드로도 작성 가능하다. 

```c#
Button btn = new Button();
btn.FontWeight = FontWeights.Bold;

WrapPanel pnl = new WrapPanel();

TextBlock txt = new TextBlock();
txt.Text = "Multi";
txt.Foreground = Brushes.Blue;
pnl.Children.Add(txt);

txt = new TextBlock();
txt.Text = "Color";
txt.Foreground = Brushes.Red;
pnl.Children.Add(txt);

txt = new TextBlock();
txt.Text = "Button";
pnl.Children.Add(txt);

btn.Content = pnl;
pnlMain.Children.Add(btn);
```

좀 더 선언적인 코드가 필요해 보인다. 



## Events in XAML 

볼수록 렌더링이 이쁘다. 아마도 scRGB 컬러 지원이 중요한 듯. 

Grid와 같은 콘트롤에 이벤트를 지정할 수 있다. 

```xaml
<Grid Name="pnlMainGrid" MouseUp="pnlMainGrid_MouseUp" Background="LightBlue">
```

코드에서도 당연히 가능하다. 그게 프로그래머는 더 편할 수 있다. 

```c#
pnlMainGrid.MouseUp += new MouseButtonEventHandler(pnlMainGrid_MouseUp);
```



# A WPF Application - Introduction 



## The Window

```xaml 
<Window x:Class="WpfApplication1.Window1"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    Title="Window1" Height="300" Width="300">
    <Grid>

    </Grid>
</Window>
```

`x:Class` 가 사용할 클래스를 지정한다. 

### Important Window Properties

- Icon 
- ResizeMode
- ShowInTaskbar
- SizeToContent 
- Topmost
- WindowStartupLocation 
- WindowState 



## Working with App.xaml

```xaml
<Application x:Class="WpfApp1.App"
             xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
             xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
             xmlns:local="clr-namespace:WpfApp1"
             StartupUri="MainWindow.xaml">
    <Application.Resources>
         
    </Application.Resources>
</Application>
```

x:Class 외에 특이한 점은 없다. 



``` xaml
 Startup="Application_Startup">
```

StartupUri 대신에 지정할 수 있다. 

WPF에 놀라운 점들이 많다. 특히, XAML과 코드가 하나로 묶여 코드 생성기로 동작한다.  GUI, 컴파일러, 코드의 삼위일체다. 



## Command-line parameters in WPF

```c#
  public class StartupEventArgs : EventArgs
    {
        public string[] Args { get; }
    }
```

시작 이벤트에 Args 배열을 갖는다. 



보는 김에 Application 클래스 인터페이스를 본다. 

```c#
//     WPF(Windows Presentation Foundation) 응용 프로그램을 캡슐화합니다.
public class Application : DispatcherObject, IHaveResources, IQueryAmbient
    {
        //     System.Windows.Application 클래스의 새 인스턴스를 초기화합니다.
        public Application();
        //     WPF 응용 프로그램의 리소스에 대한 팩 URI(Uniform Resource Identifier)를 제공하는 System.Reflection.Assembly를
        //     가져오거나 설정합니다.
        public static Assembly ResourceAssembly { get; set; }
        //     현재 System.AppDomain에 대한 System.Windows.Application 개체를 가져옵니다.
        public static Application Current { get; }
        //     응용 프로그램의 인스턴스화된 창을 가져옵니다.
        public WindowCollection Windows { get; }
        //     응용 프로그램의 주 창을 가져오거나 설정합니다.
        public Window MainWindow { get; set; }
        //     System.Windows.Application.Shutdown 메서드가 호출되게 하는 조건을 가져오거나 설정합니다.
        public ShutdownMode ShutdownMode { get; set; }
        //     응용 프로그램 범위 리소스(예: 스타일 및 브러시)의 컬렉션을 가져오거나 설정합니다.
        public ResourceDictionary Resources { get; set; }
        //     응용 프로그램이 시작될 때 자동으로 표시되는 UI를 가져오거나 설정합니다.
        public Uri StartupUri { get; set; }
        //     응용 프로그램 범위 속성의 컬렉션을 가져옵니다.
        public IDictionary Properties { get; }
        //     System.Windows.Application 개체의 System.Windows.Application.Run 메서드가 호출될 때 발생합니다.
        public event StartupEventHandler Startup;
        //     응용 프로그램이 종료되기 직전에 발생하며 취소할 수 없습니다.
        public event ExitEventHandler Exit;
        //     응용 프로그램이 더 이상 포그라운드 응용 프로그램이 아닐 때 발생합니다.
        public event EventHandler Deactivated;
        //     사용자가 로그오프하거나 운영 체제를 종료하여 Windows 세션을 끝낼 때 발생합니다.
        public event SessionEndingCancelEventHandler SessionEnding;
        //     응용 프로그램에서 예외가 throw되었지만 처리되지 않은 경우에 발생합니다.
        public event DispatcherUnhandledExceptionEventHandler DispatcherUnhandledException;
        //     응용 프로그램의 탐색기에서 새 탐색이 요청된 경우에 발생합니다.
        public event NavigatingCancelEventHandler Navigating;
        //     응용 프로그램의 탐색기에서 탐색 중인 콘텐츠를 찾은 경우에 발생합니다. 콘텐츠가 완전히 로드되지 않았을 수도 있습니다.
        public event NavigatedEventHandler Navigated;
        //     탐색 진행률 정보를 제공하기 위해 응용 프로그램의 탐색기에서 관리되는 다운로드 중에 정기적으로 발생합니다.
        public event NavigationProgressEventHandler NavigationProgress;
        //     응용 프로그램의 탐색기에서 요청된 내용을 탐색하는 동안 오류가 표시될 때 발생합니다.
        public event NavigationFailedEventHandler NavigationFailed;
        //     응용 프로그램의 탐색기에서 탐색한 콘텐츠가 로드 및 구문 분석되었으며 렌더링을 시작한 경우에 발생합니다.
        public event LoadCompletedEventHandler LoadCompleted;
        //     응용 프로그램이 포그라운드 응용 프로그램이 될 때 발생합니다.
        public event EventHandler Activated;
        //     응용 프로그램 탐색기의 StopLoading 메서드가 호출되거나 현재 탐색이 진행되는 동안 탐색기에서 새 탐색이 요청된 경우에 발생합니다.
        public event NavigationStoppedEventHandler NavigationStopped;
        //     응용 프로그램의 탐색기에서 콘텐츠 조각 탐색을 시작할 때 발생합니다. 원하는 조각이 현재 콘텐츠에 있으면 즉시 탐색이 발생하고, 원하는 조각이
        //     다른 콘텐츠에 있으면 소스 XAML 콘텐츠가 로드된 후에 탐색이 발생합니다.
        public event FragmentNavigationEventHandler FragmentNavigation;
        //     지정된 System.Uri에 있는 콘텐츠 데이터 파일에 대한 리소스 스트림을 반환합니다(WPF 응용 프로그램 리소스, 콘텐츠 및 데이터 파일
        //     참조).
        public static StreamResourceInfo GetContentStream(Uri uriContent);
        //     System.Uri에 의해 지정된 위치에 대한 쿠키를 검색합니다.
        public static string GetCookie(Uri uri);
        //     지정된 System.Uri에 있는 원본 사이트 데이터 파일에 대한 리소스 스트림을 반환합니다(WPF 응용 프로그램 리소스, 콘텐츠 및 데이터
        //     파일 참조).
        public static StreamResourceInfo GetRemoteStream(Uri uriRemote);
        //     지정된 System.Uri에 있는 리소스 데이터 파일에 대한 리소스 스트림을 반환합니다(WPF 응용 프로그램 리소스, 콘텐츠 및 데이터 파일
        //     참조).
        public static object LoadComponent(Uri resourceLocator);
        //     지정된 URI(Uniform Resource Identifier)에 있는 XAML 파일을 로드하고 XAML 파일의 루트 요소에 의해 지정된
        //     개체의 인스턴스로 변환합니다.
        public static void SetCookie(Uri uri, string value);
        //     지정된 키를 사용하여 UI(사용자 인터페이스) 리소스(예: System.Windows.Style 또는 System.Windows.Media.Brush)를
        //     검색하고 요청된 리소스가 없으면 예외를 throw합니다(XAML 리소스 참조).
        public object FindResource(object resourceKey);
        //     WPF(Windows Presentation Foundation) 응용 프로그램을 시작하고 지정된 창을 엽니다.
        public int Run(Window window);
        //     WPF(Windows Presentation Foundation) 응용 프로그램을 시작합니다.
        public int Run();
        //     응용 프로그램을 종료합니다.
        public void Shutdown();
        //     지정된 종료 코드를 운영 체제에 반환하는 응용 프로그램을 종료합니다.
        public void Shutdown(int exitCode);
        //     지정된 리소스를 검색합니다.
        public object TryFindResource(object resourceKey);
        //     System.Windows.Application.Activated 이벤트를 발생시킵니다.
        protected virtual void OnActivated(EventArgs e);
        //     System.Windows.Application.Deactivated 이벤트를 발생시킵니다.
        protected virtual void OnDeactivated(EventArgs e);
        //     System.Windows.Application.Exit 이벤트를 발생시킵니다.
        protected virtual void OnExit(ExitEventArgs e);
        //     System.Windows.Application.FragmentNavigation 이벤트를 발생시킵니다.
        protected virtual void OnFragmentNavigation(FragmentNavigationEventArgs e);
        //     System.Windows.Application.LoadCompleted 이벤트를 발생시킵니다.
        protected virtual void OnLoadCompleted(NavigationEventArgs e);
        //     System.Windows.Application.Navigated 이벤트를 발생시킵니다.
        protected virtual void OnNavigated(NavigationEventArgs e);
        //     System.Windows.Application.Navigating 이벤트를 발생시킵니다.
        protected virtual void OnNavigating(NavigatingCancelEventArgs e);
        //     System.Windows.Application.NavigationFailed 이벤트를 발생시킵니다.
        protected virtual void OnNavigationFailed(NavigationFailedEventArgs e);
        //     System.Windows.Application.NavigationProgress 이벤트를 발생시킵니다.
        protected virtual void OnNavigationProgress(NavigationProgressEventArgs e);
        //     System.Windows.Application.NavigationStopped 이벤트를 발생시킵니다.
        protected virtual void OnNavigationStopped(NavigationEventArgs e);
        //     System.Windows.Application.SessionEnding 이벤트를 발생시킵니다.
        protected virtual void OnSessionEnding(SessionEndingCancelEventArgs e);
        //     System.Windows.Application.Startup 이벤트를 발생시킵니다.
        protected virtual void OnStartup(StartupEventArgs e);
```

대상이 되는 상태에 따라 나누면 다음과 같다. 

- 애플리케이션의 진행 
- 윈도우 관리 
- 리소스 관리 
- 네비게이션 

각각은 수평화가 가능하나 하나로 통합되어 있어야 편하므로 공통의 인터페이스를 제공하는 관문으로 Application이 있다. 



## Resources

WPF는 마이크로소프트의 웹킷이자 애플리케이션 프레임워크이다. 그 만큼 좋은 개념과 기능들을 갖고 있다. 아쉬운 점은 오픈소스가 아니라는 점이다. 





























