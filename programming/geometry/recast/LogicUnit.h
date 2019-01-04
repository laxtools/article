#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <LibBase/cpp/Result.h>
#include <LibBase/cpp/InstantIdManager.h>
#include <libBase/cpp/WeightedRandom.h>
#include <LibMetaSchema/cpp/_thrift_code/characterlevel_meta_types.h>
#include <LibMetaSchema/cpp/_thrift_code/statadd_meta_types.h>
#include <LibMetaSchema/cpp/_thrift_code/unit_meta_types.h>
#include <LibMetaSchema/cpp/_thrift_code/mobileunit_meta_types.h>
#include <LibMetaSchema/cpp/_thrift_code/area_meta_types.h>
#include <LibMetaSchema/cpp/_thrift_code/mobileunit_meta_types.h>
#include <LibResourceSchema/cpp/_thrift_code/rootmotion_meta_types.h>
#include <LibProtocolUser/cpp/_thrift_code/epic_msg_area_types.h>

#include "LogicQuest.h"

#include <LibServer/cpp/UserSessionHolder.h>
#include <LibBase/cpp/Singleton.h>

#include "CrowdAgent.h"
#include "LogicSignal.h"
#include "BehaviorTree.h"
#include "SkillManager.h"
#include "AiColumnFormation.h"

class SkillAttachmentManager;
class GameCharacter;
class LogicArea;
class NavMeshManager;
class StatManager;

class LogicUnit
	: public UserSessionHolder
	, public BehaviorTree
	, public std::enable_shared_from_this<LogicUnit>
{
public:
	LogicUnit();
	LogicUnit(int32_t instanceId);
	virtual ~LogicUnit()
	{
	}

	template <typename EPIC_MSG>
	void broadcast(EPIC_MSG& epic_mesg)
	{
		std::shared_ptr<EpicPacket> epic_packet = MessageToEpicPacket(epic_mesg);
		m_signal_broadcast(epic_packet);
	}

public:
	epic::Result init(int32_t unit_meta_id);
	epic::Result spawn();
	epic::Result respawn(int32_t delta);

	//epic::Result addToCrowdAgent(bool use_random_position = false);
	epic::Result addToCrowdAgent(CrowdManager* crowd_manager = nullptr, bool use_random_position = false);			
	epic::Result removeToCrowdAgent();

	void setLogicArea(std::shared_ptr<LogicArea> logic_area);

private:
	epic::Result initDefaultUnitData(int32_t unit_meta_id);
	void initTeamSetting();
	// 캐릭터인 경우 db데이터를 받아서 갱신을 해야함.
	void initDefaultSkill();
public:
	void initCrowdAgent();

public:
	uint32_t instantId()
	{
		return *m_instantId;
	}

	int32_t unitMetaId()
	{
		return m_unit_meta_data.meta_id;
	}

	int32_t currentTime()
	{
		return m_deleta_time;
	}

	glm::vec3 unitPosition()
	{
		glm::vec3 pos;
		pos.x = static_cast<float_t>(m_unitPosition.x);
		pos.y = static_cast<float_t>(m_unitPosition.y);
		pos.z = static_cast<float_t>(m_unitPosition.z);
		return pos;
	}
	glm::vec3 destPosition()
	{
		glm::vec3 pos;
		pos.x = static_cast<float_t>(m_destPosition.x);
		pos.y = static_cast<float_t>(m_destPosition.y);
		pos.z = static_cast<float_t>(m_destPosition.z);
		return pos;
	}
	glm::vec3 spawnPosition()
	{
		glm::vec3 pos;
		pos.x = static_cast<float_t>(m_spawnPosition.x);
		pos.y = static_cast<float_t>(m_spawnPosition.y);
		pos.z = static_cast<float_t>(m_spawnPosition.z);
		return pos;
	}

	bool changePlayState(meta_define::UnitPlayState_e::type play_state);
	void setSkillStateTimer(skill_meta::SkillType_e::type skill_type, int32_t time_value);
	void unsetPlayStateTimer();
	bool isPlayState(meta_define::UnitPlayState_e::type play_state);
	meta_define::UnitPlayState_e::type getPlayState()
	{
		return m_playstate;
	}

	int32_t addStat(meta_define::StatType_e::type statType, int32_t value);
	int32_t getStat(meta_define::StatType_e::type statType);
	int32_t getUnitStat(meta_define::StatType_e::type statType);
	int32_t currentHp() { return getStat(meta_define::StatType_e::CurrentHp); }
	int32_t addCurrentHp(int32_t hp) { return addStat(meta_define::StatType_e::CurrentHp, hp); }
	void setLevelAbilityData(meta_define::UnitAbility ability_meta_data);

	bool isSpawned();
	void setSpawned();
	bool isDead();
	void dead();
	void resetTarget();

	bool isUnitType(unit_meta::UnitType_e::type unit_type)
	{
		return (m_unit_meta_data.unitType == unit_type);
	}

	unit_meta::UnitType_e::type unitType()
	{
		return m_unit_meta_data.unitType;
	}

	void onKillTarget(std::shared_ptr<LogicUnit> defender);
	epic_define::UnitPosition randomCircle(epic_define::UnitPosition center, float radius);

	void update(int32_t delta_time);
	void updateStateTimer(int32_t delta_time);

	//bool checkSkillCondtion(mobileunit_meta::UseSkillConditionType_e::type use_skill_type);
	//bool checkConditionValue(mobileunit_meta::UseSkillConditionType_e::type use_skill_type, mobileunit_meta::BattleCondition condition);
	//bool checkApproachDistance();
	//bool checkUseSkillDistance();
	

	bool moveToTarget(bool checkTarget = false, bool sendBroadcast = false);
	bool moveToTarget(glm::vec3 dest_position, bool notify, unit_meta::AniType_e::type ani_type = unit_meta::AniType_e::Run);
	bool moveToTarget(glm::vec3 dest_position, float move_speed);
	void setNotifyMoveUnit(unit_meta::AniType_e::type ani_type, _out epic_msg_area::MoveInfo &info);
	void changeUnitSpeed(float speed);
	void warp(trigger_meta::WarpArea warp_area);
	void warp(epic_define::UnitPosition warp_pos);

	epic::Result equipVehicle(uint32_t item_db_id, int32_t vehicle_id);
	epic::Result unequipVehicle(uint32_t item_db_id, int32_t vehicle_id);
	int32_t getVehicle();

	void setLogicUnitInstanceId(int32_t instanceId);


	//===========================================================================
	// behavior
	void setAIState(string_t state_string);

	bool findable();
	bool skillUsable();
	bool checkTargetDistance(glm::vec3 targetPosition);
	bool checkTargetAttackable(std::shared_ptr<LogicUnit> target);
	bool checkPatrolPossible();
	bool checkBackOutPossible();
	bool checkNestCondition();

	bool enterPatrol();

	bool findTarget(meta_define::TargetType_e::type team);
	bool hasTarget(meta_define::TargetType_e::type team); //타겟이 있는지 체크

	bool approachStart();
	bool approachUpdate();

	bool backOut();

	bool useNestConditionSkill();

	bool useSkill(skill_meta::AttackType_e::type attack_type);
	bool castSkill(boost::shared_ptr<Skill> skill);
	void shotSkill(boost::shared_ptr<Skill> skill);
	void hitSkill(boost::shared_ptr<Skill> skill);
	void endSkill(boost::shared_ptr<Skill> skill);
	
	void hitByUserSkill();
	boost::shared_ptr<Skill> selectSkill(skill_meta::AttackType_e::type skill_type);
	void resetCurrentSkill(int32_t skill_meta_id);

	void onAttachSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment);
	void onDetachSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment);
	void onTickSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment);



	bool hasSkillGroup()
	{
		return (m_mobileunit_meta_data.skillGroups.size() > 0);
	}
	void setNextSkillUsableTime();

	//void setCommander(std::shared_ptr<LogicUnit> commnader);



	//================================================================
	void areaBroadcast(std::shared_ptr<EpicPacket> epic_packet);
	void addUnitMoveMsg(epic_msg_area::MoveInfo& moveinfo);

	epic::Result applyEquipSkill(std::vector<item_meta::EquipSkillBuff>& equipSkills);
	epic::Result applyUnequipSkill(std::vector<item_meta::EquipSkillBuff>& unequipSkills);
	
	boost::shared_ptr<Skill> takeAndAddSkill(int32_t skill_meta_id);

	void setRootMotionInfo(int meta_id, const char* root_motion_name);	// for LogicClient
	bool hasRootMotionClip(string_t clip_name);
	bool takeRootMotionClip(string_t clip_name, rootmotion_meta::MotionClips& out_clips);
	epic_define::Float3 takeRootMotionDestPosition(const char* clip_name);
	epic_define::Float3 takeRootMotionFramePosition(const char* clip_name, float frame);

public:
	std::shared_ptr<InstantId> m_instantId;
	int32_t m_client_instance_id;	//클라이언트내 LogicUnit이 사용하는 서버의 InstanceID

	meta_define::UnitPlayState_e::type m_playstate{ meta_define::UnitPlayState_e::Playing }; // 플레이상태
	int32_t m_skillstate_timer{ 0 };
	int32_t m_elapsed_state{ 0 };

	//unit_meta::UnitType_e::type m_unittype{ unit_meta::UnitType_e::_BEGIN };
	epic_define::UnitPosition m_unitPosition; //현재 좌표
	epic_define::UnitPosition m_destPosition; //이동시 목표 좌표
	epic_define::UnitPosition m_spawnPosition; //스폰 시 좌표
	glm::vec3 m_direction;

	std::weak_ptr<LogicUnit> m_target_unit;
	//std::weak_ptr<LogicUnit> m_commander_unit;
	CrowdAgent* m_crowd_agent{ nullptr };

	int32_t m_unit_meta_id{ 0 };
	int32_t m_client_state{ 0 };
	bool m_dead{ true };
	bool m_critical{ false };
	bool m_can_attack{ true };

	int32_t m_curent_hp{ 0 };		// CurrentHp()로 대체 필요함 statmanager로 통합
	float_t m_move_speed{ 0 };

	processSkillHit m_process_hit_skill;	// Hit 전송을 위한 타이머

public:
	int32_t m_respawnDelta{ 0 };
	int32_t m_area_meta_id;
	int32_t m_vehicle_id{ 0 }; //탈것

	deploy_meta::Spawner m_spawner_meta;
	unit_meta::unit_data m_unit_meta_data;
	mobileunit_meta::mobileunit_data m_mobileunit_meta_data;

	characterlevel_meta::characterlevel_data m_characterlevelData;
	std::shared_ptr<LogicQuest> m_logic_quest;
	std::weak_ptr<GameCharacter> m_game_character;

private:
	bool m_attack_distance_ok{ false };
	bool m_spawned{ false };

public:
	signal_kill_unit_t m_signal_kill_unit;
	signal_dead_unit_t m_signal_dead_unit;
	signal_send_packet_t m_signal_broadcast;
	signal_send_multicast_packet_t m_signal_multicast_party;

	std::weak_ptr<LogicArea> m_private_logic_area;
	std::weak_ptr<LogicArea> m_logic_area;
	boost::weak_ptr<NavMeshManager> m_nav_mesh_manager;
	
	boost::weak_ptr<Skill> m_hit_skill;
	int32_t m_next_hit_time{ 0 };
	int32_t m_hit_skill_id{ 0 };
public:

	unit_meta::TeamType_e::type m_origin_team{ unit_meta::TeamType_e::Neutral };
	unit_meta::TeamType_e::type m_current_team{ unit_meta::TeamType_e::Neutral };

	SkillManager m_skill_manager;

public:
	meta_define::TargetType_e::type m_findtarget_type{ meta_define::TargetType_e::type::_BEGIN };;
	gimmick_meta::gimmick_data m_gimmick_meta_data; // m_gimmick_meta_data로 바꿀것.
	epic_define::ObjectStateType_e::type m_object_state{ epic_define::ObjectStateType_e::_BEGIN };
	bool m_client_unit{ false };

	boost::shared_ptr<SkillAttachmentManager> m_skill_attachment_manager;
	meta_define::UnitAbility m_character_ability; //캐릭터 생성시 발생되는 고유 능력치
	boost::shared_ptr<StatManager> m_stat_manager; // 확장능력치
	boost::shared_ptr<rootmotion_meta::RootMotions> m_root_motion; //루트모션정보
	rootmotion_meta::MotionClips m_current_motion_clips; //현재 루트모션

	dtCrowdAgentParams m_crowd_agent_param;
	dtObstacleAvoidanceParams m_obstacle_avoidance_params;

	int32_t m_deleta_time{ 0 };
	AiColumnFormation m_formation;
	int32_t m_formation_slot{ -1 };

private:
	bool m_autoable{ false };
	bool m_lock_state{ false };
	bool m_ai_spawn_ready{ false };
	bool m_enable_ai_state{ false };
	bool m_back_out{ false };
	bool m_enable_patrol{ false };
	bool m_has_root_motion{ false };

	int32_t m_ai_elapsed{ 0 };
	int32_t m_ai_patrol_find_tic{ 300 };
	int32_t m_ai_next_tic{ 300 };		// 기본 300ms
	int32_t m_ai_spawn_ready_time{ 0 };
	string_t m_ai_state;

	int32_t m_skill_begin_time{ 0 }; //
	int32_t m_next_skill_usable_time{ 0 };//다음에 스킬을 사용할 수 있는 기간.

	float_t m_angle;

	bool m_formation_moveable{ true };
	string_t m_root_motion_name;

public:
	quest_meta::QuestType_e::type m_quest_type{ quest_meta::QuestType_e::_BEGIN };
	int32_t m_party_instantId{ 0 };

	meta_define::JobType_e::type m_job_type;

	// 장착 아이템 정보
	std::vector<int32_t>  m_equip_items;

	// M3 하드코딩 보호 퀘스트일때는 타겟을 바꾸지 않는다.
	// M3이후에 삭제
	bool m_target_locked{ false };

private:
	int32_t m_increase_hp_time{ 0 };

public:
	void increase_hp(int32_t dt); ///fixme 3초마다 meta_define::StatType_e::HPRegen를 증가시킨다. 마일스톤 2.7용. 이 후에 패시브 스킬로 대체해야 한다.


};
