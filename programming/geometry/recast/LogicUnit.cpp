#include "preheader.h"

#include <LibMetaSchema/cpp/_thrift_code/meta_define_types.h>
#include <LibProtocolUser/cpp/_thrift_code/epic_msg_skill_types.h>
#include <LibProtocolUser/cpp/_thrift_code/epic_msg_buff_types.h>
#include <LibProtocolUser/cpp/_thrift_code/epic_msg_area_types.h>
#include <LibMetaManager/cpp/MetaManager.h>
#include <LibBase/cpp/Random.h>
#include "LogicUnit.h"
#include "NavMeshManager.h"
#include "SkillAttachment.h"
#include "LogicUnitManager.h"
#include "StatManager.h"
#include "RootMotionManager.h"
#include "LogicArea.h"
#include "Skill.h"
#include "LogicDefine.h"
#include <LibBase/cpp/EpicMath.h>

#define MONSTER_PATROL_UPDATE		12000	// Patrol 6초
#define MONSTER_PATROL_SEARCH		1000	// Patrol중 타겟search 1초
#define MONSTER_NORMAL_UPDATE		300		// 일반 업데이트 300ms
#define MONSTER_ATACKED_DELAY		500		// 피격 딜레이 600ms
#define APPROACH_ERROR_BOUND		0.3f
#define ATTACK_RANGE_MARGIN			0.4f	// Collision

#define VEHICLE_SPEED		6	// 추후 탈것 관련 meta에 추가되어야 한다.



LogicUnit::LogicUnit()
{
	ScopedLoggerName("logicunit");
	m_instantId = epic::Singleton<InstantIdManager>()->alloc();

	LOG_DEBUG("create skill attachment manager");
	m_skill_attachment_manager = boost::make_shared<SkillAttachmentManager>();

	LOG_DEBUG("create stat manager");
	m_stat_manager = boost::make_shared<StatManager>();

	m_root_motion = boost::make_shared<rootmotion_meta::RootMotions>();
	LOG_DEBUG("logic unit create complete");
}


LogicUnit::LogicUnit(int32_t instanceId)
{
	ScopedLoggerName("client - logicunit");
	m_instantId = std::make_shared<InstantId>(instanceId);

	LOG_DEBUG("create skill attachment manager");
	m_skill_attachment_manager = boost::make_shared<SkillAttachmentManager>();

	LOG_DEBUG("create stat manager");
	m_stat_manager = boost::make_shared<StatManager>();

	m_root_motion = boost::make_shared<rootmotion_meta::RootMotions>();
	LOG_DEBUG("logic unit create complete");
}


epic::Result LogicUnit::init(int32_t unit_meta_id)
{
	epic::Result epic_result;
	m_unit_meta_id = unit_meta_id;
	m_root_motion_name = "";
	m_ai_state = "null";
	m_process_hit_skill.clear();

	initDefaultUnitData(unit_meta_id);
	initDefaultSkill();
	initCrowdAgent();

	m_destPosition = m_unitPosition;

	return epic_result.SetOk();
}

epic::Result LogicUnit::spawn()
{
	epic::Result epic_result;

	if (isSpawned())
	{
		return epic_result.SetFail(sformat(" - already spawned - {}:{}", instantId(), m_unit_meta_data.meta_name));
	}
	setSpawned();

	initTeamSetting();

	m_curent_hp = m_stat_manager->getStat(meta_define::StatType_e::Hp);
	m_move_speed = m_mobileunit_meta_data.runSpeed;

	// add unit to crowd agent
	if (m_spawner_meta.radius > 0)
	{
		epic_result = addToCrowdAgent(nullptr, true);
		if (unit_meta::UnitType_e::Gimmick == m_unit_meta_data.unitType)
		{
			LOG_INFO("gimick random pos");
		}
	}
	else
	{
		epic_result = addToCrowdAgent(false);
	}

	m_unitPosition = m_spawnPosition;

	if (m_client_unit)
	{
		LOG_INFO("client spawn unit position : {} unit name : {}", m_unitPosition, instantId());
	}
	else
	{
		LOG_INFO("server spawn unit position : {} unit name : {}", m_unitPosition, instantId());
	}

	//LOG_INFO("spawn position {}, name : {}", m_unitPosition, m_unit_meta_data.sname);
	if (epic_result.Fail())
	{
		return epic_result;
	}

	if (m_unit_meta_data.unitType != unit_meta::UnitType_e::Gimmick && m_unit_meta_data.unitType != unit_meta::UnitType_e::Prop 
		&& m_unit_meta_data.unitType != unit_meta::UnitType_e::BattleNpc && m_unit_meta_data.unitType != unit_meta::UnitType_e::Npc)
	{
		changeUnitSpeed(m_move_speed);
	}
	else
	{
		m_move_speed = 0;
		changeUnitSpeed(m_move_speed);
	}

	//currentStrength = m_character_ability.strength;
	//currentIntelligence = m_character_ability.intelligence;
	//currentDexterity = m_character_ability.dexterity;

	if (m_unit_meta_data.unitType == unit_meta::UnitType_e::Gimmick)
	{
		auto gimmick_collection = epic::Singleton<MetaManager>()->collection<gimmick_meta::container>("gimmick");
		auto gimmick_iterator = gimmick_collection->infos.find(m_unit_meta_data.gimmick_meta_id);
		if (gimmick_iterator == gimmick_collection->infos.end())
		{
			LOG_ERROR(sformat("unit gimmick err = unit id : {}", m_unit_meta_data.meta_id));
		}
		else
		{
			m_gimmick_meta_data = gimmick_iterator->second;
			m_object_state = m_gimmick_meta_data.default_state;
		}
	}
	m_ai_spawn_ready = true;
	return epic::Result().SetOk();
}

epic::Result LogicUnit::respawn(int32_t delta)
{
	if (m_dead && m_spawner_meta.respawnTime > 0)
	{
		m_respawnDelta += delta;
		int32_t meta_respawn_time = m_spawner_meta.respawnTime;
		if (m_respawnDelta > (meta_respawn_time * 1000 * 2))
		{
			int32_t random_delta = meta_respawn_time * 1000;
			random_delta = epic::random(0, random_delta);
			m_respawnDelta = random_delta;
			LOG_DEBUG("respawn call {}:{}", instantId(), m_unit_meta_data.meta_name);
			return spawn();
		}
	}
	return epic::Result().SetFail();
}



void LogicUnit::setLogicUnitInstanceId(int32_t instanceId)
{
	m_client_instance_id = instanceId;
}


epic_define::UnitPosition LogicUnit::randomCircle(epic_define::UnitPosition center, float radius)
{
	epic_define::UnitPosition position;
	position.__set_z(0.0f);
	position.__set_angle(0.0f);
	float radius2 = radius * 2;
	position.__set_x((epic::random(-1.0f, 1.0f) * radius2) - radius + center.x);
	position.__set_z((epic::random(-1.0f, 1.0f) * radius2) - radius + center.z);
	return position;
}



void LogicUnit::setSkillStateTimer(skill_meta::SkillType_e::type skill_type, int32_t time_value)
{
	switch (skill_type)
	{
	case skill_meta::SkillType_e::Dodge:
		changePlayState(meta_define::UnitPlayState_e::SkillDodge);
		break;
	case skill_meta::SkillType_e::Special:
		changePlayState(meta_define::UnitPlayState_e::SkillSpecial);
		break;
	case skill_meta::SkillType_e::Normal:
		changePlayState(meta_define::UnitPlayState_e::SkillNormal);
		break;
	case skill_meta::SkillType_e::Active:
		changePlayState(meta_define::UnitPlayState_e::SkillActive);
		break;
	case skill_meta::SkillType_e::Counter:
		changePlayState(meta_define::UnitPlayState_e::UseSkill);
		break;
	default:
		changePlayState(meta_define::UnitPlayState_e::UseSkill);
		break;
	}
	m_skillstate_timer = time_value;
	LOG_DEBUG("  setSkillStateTimer {}:{}", skill_type, time_value);
}


void LogicUnit::unsetPlayStateTimer()
{
	LOG_DEBUG("reset UnitState {}:{} = {}", instantId(), m_unit_meta_data.meta_name, m_playstate);
	m_skillstate_timer = 0;
	m_playstate = meta_define::UnitPlayState_e::Playing;	//되돌릴 상태를 저장여부는 추후 
}



bool LogicUnit::changePlayState(meta_define::UnitPlayState_e::type play_state)
{
	if (play_state == meta_define::UnitPlayState_e::QuestReward && isPlayState(meta_define::UnitPlayState_e::NpcTalk))
	{
		return false;
	}
	m_playstate = play_state;
	return true;
}

bool LogicUnit::isPlayState(meta_define::UnitPlayState_e::type play_state)
{
	if (m_playstate == play_state)
	{
		return true;
	}
	
	return false;
}


int32_t LogicUnit::getStat(meta_define::StatType_e::type statType)
{
	return m_stat_manager->getStat(statType);
}
int32_t LogicUnit::getUnitStat(meta_define::StatType_e::type statType)
{
	return m_stat_manager->getUnitStat(statType);
}
int32_t LogicUnit::addStat(meta_define::StatType_e::type statType, int32_t value)
{
	return m_stat_manager->addStat(statType, value);
}

bool LogicUnit::isSpawned()
{
	return m_spawned;
}


bool LogicUnit::isDead()
{
	return m_dead;
}

// Monster Dead와 Player Dead의 별도 처리 필요
// Moster는 respawn하지만 Player는 부활하는데, agent를 다시 생성하는지 확인 필요
void LogicUnit::dead()
{
	m_dead = true;
	m_spawned = false;
	m_enable_ai_state = false;
	m_ai_spawn_ready = false;
	
	resetTarget();
	unequipVehicle(0, 0);

	if (isUnitType(unit_meta::UnitType_e::Pc))
	{
		//
	}
	else
	{
		if (isUnitType(unit_meta::UnitType_e::BattleNpc))
		{
			m_spawnPosition = m_unitPosition;
		}
		if (!m_signal_dead_unit.empty())
		{
			LOG_DEBUG("monster Dead signal call {}:{}", instantId(), m_unit_meta_data.meta_name);
			m_signal_dead_unit(unitMetaId());
		}

		removeToCrowdAgent();
	}
}

// revival 시에도 호출됨
void LogicUnit::setSpawned()
{
	m_spawned = true;
	m_dead = false;
}

void LogicUnit::onKillTarget(std::shared_ptr<LogicUnit> defender)
{
	m_signal_kill_unit(defender);
}


void LogicUnit::resetTarget()
{
	if (m_target_unit.expired() == false && m_target_locked == false)
	{
		m_target_unit.reset();
	}
}


void LogicUnit::initTeamSetting()
{
	this->m_origin_team = m_unit_meta_data.teamType;
	this->m_current_team = m_unit_meta_data.teamType;
}

epic::Result LogicUnit::initDefaultUnitData(int32_t unit_meta_id)
{
	auto unit_collection = epic::Singleton<MetaManager>()->collection<unit_meta::container>("unit");
	auto unit_iterator = unit_collection->infos.find(m_unit_meta_id);
	if (unit_collection->infos.end() == unit_iterator)
	{
		return epic::Result().SetFail(sformat("unit meta:{} not found", unit_meta_id));
	}
	m_unit_meta_data = unit_iterator->second;

	// set mobileunit meta data : 존재하지 않을 수 있음.
	auto mobileunit_collection = epic::Singleton<MetaManager>()->collection<mobileunit_meta::container>("mobileunit");
	auto mobileunit_iterator = mobileunit_collection->infos.find(m_unit_meta_data.mobileunit_meta_id);
	if (mobileunit_collection->infos.end() != mobileunit_iterator)
	{
		m_mobileunit_meta_data = mobileunit_iterator->second;
	}

	setLevelAbilityData(m_unit_meta_data.ability);
	LOG_INFO("initDefaultUnitData::setLevelAbilityData");

	//m_root_motion = epic::Singleton<RootMotionManager>()->takeRootMotions(m_unit_meta_data.rootmotionName);
	setRootMotionInfo(m_unit_meta_data.meta_id, m_unit_meta_data.rootmotionName.c_str());

	return epic::Result().SetOk();
}


void LogicUnit::initDefaultSkill()
{
	LOG_INFO("LogicUnit::initDefaultSkill({},{},{}): skill group size: {}", instantId(), m_unit_meta_id, m_unit_meta_data.meta_name, m_mobileunit_meta_data.skillGroups.size());
	if (isUnitType(unit_meta::UnitType_e::Boss))
	{
		// Add Boss Skill Group 
	}
	else
	{
		m_skill_manager.addSkillGroups(m_mobileunit_meta_data.skillGroups, this);
	}
	m_skill_attachment_manager->m_signal_skill_attachment.connect(boost::bind(&LogicUnit::onAttachSkillAttachment, this, _1));
}


void LogicUnit::initCrowdAgent()
{
	
	m_crowd_agent_param.collisionQueryRange = 3.2f;
	m_crowd_agent_param.height = 1.8f;
	m_crowd_agent_param.maxAcceleration = 300.0f;
	m_crowd_agent_param.maxSpeed = 4.0f;
	m_crowd_agent_param.pathOptimizationRange = 12.0f;
	m_crowd_agent_param.useIntegrate = false;
	m_crowd_agent_param.radius = m_unit_meta_data.agentSize;

	/*if (m_unit_meta_data.radius < 1.0f)
	{
	m_crowd_agent_param.radius = 1.0f;
	}*/
	//m_crowd_agent_param.radius = m_unit_meta_data.radius * 0.1f;
	/*if (m_unit_meta_data.height < 1.0)
	{
	m_unit_meta_data.height = 1.0;
	}*/
	m_crowd_agent_param.height = m_unit_meta_data.height;
	m_crowd_agent_param.separationWeight = 3.2f;
	m_crowd_agent_param.obstacleAvoidanceType = 0;
	m_crowd_agent_param.updateFlags = UpdateFlags::DT_CROWD_OPTIMIZE_TOPO & UpdateFlags::DT_CROWD_OPTIMIZE_VIS;
}




void LogicUnit::setLevelAbilityData(meta_define::UnitAbility ability_meta_data)
{
	m_character_ability.__set_AttackPower(ability_meta_data.AttackPower);
	m_character_ability.__set_Defense(ability_meta_data.Defense);
	m_character_ability.__set_Hp(ability_meta_data.Hp);
	m_character_ability.__set_Critical(ability_meta_data.Critical);
	m_character_ability.__set_CriticalDamage(ability_meta_data.CriticalDamage);
	m_character_ability.__set_MoveSpeed(ability_meta_data.MoveSpeed);
	m_character_ability.__set_HPRegen(ability_meta_data.HPRegen);
	m_character_ability.__set_AttackSpeed(ability_meta_data.AttackSpeed);
	m_character_ability.__set_MeeleDamageDown_Rate(ability_meta_data.MeeleDamageDown_Rate);
	m_character_ability.__set_RangeDamageDown_Rate(ability_meta_data.RangeDamageDown_Rate);

	m_stat_manager->setInitialStat(m_character_ability);
	m_stat_manager->ComputeBuffStat();		// 버프 재계산
}

void LogicUnit::setLogicArea(std::shared_ptr<LogicArea> logic_area)
{
	m_logic_area = logic_area;
}

//epic::Result LogicUnit::addToCrowdAgent(bool use_random_position)
//{
//	glm::vec3 unit_position = glm::vec3(m_spawner_meta.centerPosition.x, m_spawner_meta.centerPosition.y, m_spawner_meta.centerPosition.z);
//	auto logic_area = m_logic_area.lock();
//	if (!logic_area)
//	{
//		return epic::Result().SetFail(sformat("logic_area is null"));
//	}
//	auto nav_mesh_manager = logic_area->m_nav_mesh_manager.lock();
//	if (!nav_mesh_manager)
//	{
//		return epic::Result().SetFail(sformat("nav_mesg_manager is null"));
//	}
//
//	m_nav_mesh_manager = nav_mesh_manager;
//
//	if (use_random_position)
//	{
//		//unit_position = nav_mesh_manager->takeRandomPosition(unit_position, m_spawner_meta.radius);
//		unit_position = nav_mesh_manager->computeRandomPosition(unit_position, m_spawner_meta.radius);
//	}
//
//	if (isUnitType(unit_meta::UnitType_e::Pc))
//	{
//		unit_position = unitPosition();
//	}
//
//	m_spawnPosition.x = unit_position.x;
//	m_spawnPosition.y = unit_position.y;
//	m_spawnPosition.z = unit_position.z;
//	m_spawnPosition.angle = m_spawner_meta.centerPosition.angle;
//
//	m_crowd_agent = nav_mesh_manager->m_crowd_manager->addAgent(unit_position, m_crowd_agent_param);
//	if (m_client_unit)
//	{
//		LOG_INFO("client spawn position : {} unit name : {}", m_spawnPosition, instantId());
//	}
//	else
//	{
//		LOG_INFO("server spawn position : {} unit name : {}", m_spawnPosition, instantId());
//	}
//
//	//Low (11)
//	/*m_obstacle_avoidance_params.velBias = 0.5f;
//	m_obstacle_avoidance_params.adaptiveDivs = 5;
//	m_obstacle_avoidance_params.adaptiveRings = 2;
//	m_obstacle_avoidance_params.adaptiveDepth = 1;*/
//
//	//m_crowd_agent
//
//	//{
//	//	//Medium (22)
//	m_obstacle_avoidance_params.velBias = 0.5f;
//	m_obstacle_avoidance_params.adaptiveDivs = 5;
//	m_obstacle_avoidance_params.adaptiveRings = 2;
//	m_obstacle_avoidance_params.adaptiveDepth = 2;
//
//	//	//Good (45)
//	//	m_obstacle_avoidance_params.velBias = 0.5f;
//	//	m_obstacle_avoidance_params.adaptiveDivs = 7;
//	//	m_obstacle_avoidance_params.adaptiveRings = 2;
//	//	m_obstacle_avoidance_params.adaptiveDepth = 3;
//
//	//	//High (66)
//	//	m_obstacle_avoidance_params.velBias = 0.5f;
//	//	m_obstacle_avoidance_params.adaptiveDivs = 7;
//	//	m_obstacle_avoidance_params.adaptiveRings = 3;
//	//	m_obstacle_avoidance_params.adaptiveDepth = 3;
//	//}
//	m_crowd_agent->setObstacleAvoidanceParams(0, m_obstacle_avoidance_params);
//	m_crowd_agent->setCollisionPriority(m_crowd_agent->m_manager_index, 0.5f);
//
//	/*if (isUnitType(unit_meta::UnitType_e::Pc))
//	{
//	m_crowd_agent->setCollisionPriority(m_crowd_agent->m_manager_index, 0.5f);
//	}
//	else
//	{
//	m_crowd_agent->setCollisionPriority(m_crowd_agent->m_manager_index, 0.5f);
//	}*/
//
//	return epic::Result().SetOk();
//}


epic::Result LogicUnit::addToCrowdAgent(CrowdManager* crowd_manager, bool use_random_position)
{
	glm::vec3 unit_position = glm::vec3(m_spawner_meta.centerPosition.x, m_spawner_meta.centerPosition.y, m_spawner_meta.centerPosition.z);
	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		return epic::Result().SetFail(sformat("logic_area is null"));
	}
	auto nav_mesh_manager = logic_area->m_nav_mesh_manager.lock();
	if (!nav_mesh_manager)
	{
		return epic::Result().SetFail(sformat("nav_mesg_manager is null"));
	}

	m_nav_mesh_manager = nav_mesh_manager;

	if (use_random_position)
	{
		unit_position = nav_mesh_manager->takeRandomPosition(unit_position, m_spawner_meta.radius);
		//unit_position = nav_mesh_manager->computeRandomPosition(unit_position, m_spawner_meta.radius);
	}

	if (isUnitType(unit_meta::UnitType_e::Pc))
	{
		unit_position = unitPosition();
	}

	m_spawnPosition.x = unit_position.x;
	m_spawnPosition.y = unit_position.y;
	m_spawnPosition.z = unit_position.z;
	m_spawnPosition.angle = m_spawner_meta.centerPosition.angle;

	m_crowd_agent = nav_mesh_manager->add_crowd_agent( crowd_manager, unit_position, m_crowd_agent_param);
	
	if (nullptr == m_crowd_agent)
	{
		return epic::Result().SetFail(sformat("LogicUnit::addToCrowdAgent crowd_manager->addAgent returned null"));
	}
		
	if (m_client_unit)
	{
		LOG_INFO("client spawn position : {} unit name : {}", m_spawnPosition, instantId());
	}
	else
	{
		LOG_INFO("server spawn position : {} unit name : {}", m_spawnPosition, instantId());
	}

	m_obstacle_avoidance_params.velBias = 0.5f;
	m_obstacle_avoidance_params.adaptiveDivs = 5;
	m_obstacle_avoidance_params.adaptiveRings = 2;
	m_obstacle_avoidance_params.adaptiveDepth = 2;

	//m_crowd_agent->setObstacleAvoidanceParams(0, m_obstacle_avoidance_params);
	//m_crowd_agent->setCollisionPriority(m_crowd_agent->m_manager_index, 0.5f);

	return epic::Result().SetOk();
}


void LogicUnit::warp(trigger_meta::WarpArea warp_area)
{
	glm::vec3 position;
	rcnNavmeshPoint nav_mesh_pt;

	if (!m_crowd_agent)
	{
		return;
	}

	position.x = warp_area.x;
	position.y = warp_area.y;
	position.z = warp_area.z;
	m_angle = warp_area.angle;

	auto nav_mesh_manager = this->m_nav_mesh_manager.lock();
	nav_mesh_manager->nearestPoint(position, &nav_mesh_pt);
	position.x = nav_mesh_pt.point[0];
	position.y = nav_mesh_pt.point[1];
	position.z = nav_mesh_pt.point[2];

	//nav_mesh_manager->m_crowd_manager->pushAgentPosition(m_crowd_agent, position);
	if (m_crowd_agent && m_crowd_agent->m_manager)
	{
		m_crowd_agent->m_manager->pushAgentPosition(m_crowd_agent, position);
	}
	else
	{
		return;
	}

	m_unitPosition.x = position.x;
	m_unitPosition.y = position.y;
	m_unitPosition.z = position.z;
	m_unitPosition.angle = m_angle;
	m_destPosition = m_unitPosition;

	if (m_crowd_agent && m_crowd_agent->m_manager)
	{
		CrowdManager* manager = this->m_crowd_agent->m_manager;
		if (manager->m_agent_states.size() >= m_crowd_agent->m_manager_index + 1)
		{
			rcnCrowdAgentCoreData initial_state;
			//nav_mesh_manager->m_crowd_manager->dtcaGetAgentCoreData(m_crowd_agent->m_root, &initial_state);
			m_crowd_agent->m_manager->dtcaGetAgentCoreData(m_crowd_agent->m_root, &initial_state);
			manager->m_agent_states[m_crowd_agent->m_manager_index] = initial_state;
		}
	}

	//moveToTarget(destPosition(), true);

	//LOG_INFO("warp pos : {}", m_destPosition);

	// *** zone이 바뀐 경우 recast를 전부 교체해야 한다. - 처리 되어야 함
}

/**
	@author: duragon
	@data: 2016/3/8
	@desc: rootMotion 관련 모듈
	@param
*/
void LogicUnit::setRootMotionInfo(int meta_id, const char* root_motion_name)
{
	m_unit_meta_id = meta_id;
	m_root_motion_name = root_motion_name;
	if (!m_root_motion_name.empty() && m_root_motion_name.length() > 2)
	{
		m_has_root_motion = true;
		m_root_motion = epic::Singleton<RootMotionManager>()->takeRootMotions(m_root_motion_name);
		//LOG_INFO("LogicUnit::setRootMotionInfo({},{},{}) : root_motion_name : {}", instantId(), m_unit_meta_id, m_unit_meta_data.meta_name, m_root_motion_name);
		return;
	}
	//LOG_INFO("LogicUnit::setRootMotionInfo({},{},{}): root_motion_name is NULL", instantId(), m_unit_meta_id, m_unit_meta_data.meta_name);
}

bool LogicUnit::hasRootMotionClip(string_t clip_name)
{
	if (m_has_root_motion)
	{
		auto it = m_root_motion->mapMotions.find(clip_name);
		if (it != m_root_motion->mapMotions.end())
		{
			return true;
		}
	}
	return false;
}

bool LogicUnit::takeRootMotionClip(string_t clip_name, rootmotion_meta::MotionClips& out_clips)
{
	if (m_has_root_motion)
	{
		auto it = m_root_motion->mapMotions.find(clip_name);
		if (it != m_root_motion->mapMotions.end())
		{
			out_clips = m_root_motion->mapMotions[clip_name];
			return true;
		}
	}
	return false;
}

epic_define::Float3 LogicUnit::takeRootMotionDestPosition(const char* clip_name)
{
	if (m_has_root_motion)
	{
		auto it = m_root_motion->mapMotions.find(clip_name);
		if (it != m_root_motion->mapMotions.end())
		{
			return m_root_motion->mapMotions[clip_name].destination;
		}
	}
	return epic_define::Float3();
}

epic_define::Float3 LogicUnit::takeRootMotionFramePosition(const char* clip_name, float frame)
{
	if (!m_has_root_motion)
	{
		return epic_define::Float3();	// zero
	}
	if (m_current_motion_clips.name != clip_name)
	{
		if (takeRootMotionClip(clip_name, m_current_motion_clips) == false)
		{
			return epic_define::Float3();	// zero
		}
	}
	if (m_current_motion_clips.frameCount <= frame)
	{
		return epic_define::Float3();	// zero
	}
	int iframe = (int)frame;
	epic_define::Float3 current_frame = m_current_motion_clips.listPosition[iframe];
	return epic::lerpF3(frame - (float)iframe, current_frame, m_current_motion_clips.listPosition[iframe + 1]);
}

/**
	@author: duragon
	@data: 2016/2/24
	@desc: 장비 장착시 스킬사용 목록 (기본, 강화, 진화)
	스킬에 적용되어 있는 ShotSkillAttachment를 적용한다.
	@param
*/
epic::Result LogicUnit::applyEquipSkill(std::vector<item_meta::EquipSkillBuff>& equipSkillIds)
{
	epic::Result epic_result;
	auto skill_collection = epic::Singleton<MetaManager>()->collection<skill_meta::container>("skill");

	for (auto skillKey : equipSkillIds)
	{
		NAMED_DEBUG("logicunit.equip", "   -- unit apply EquipSkill:{}, {}", skillKey.equipItemId, skillKey.skillMetaId);
		auto it = skill_collection->infos.find(skillKey.skillMetaId);
		m_skill_attachment_manager->attach(skillKey, it->second.shotSkillAttachment);
	}

	NAMED_DEBUG("logicunit.equip", "ALL: {}", m_stat_manager->toStatString());

	return epic_result.SetOk();
}

epic::Result LogicUnit::applyUnequipSkill(std::vector<item_meta::EquipSkillBuff>& unequipSkillIds)
{
	epic::Result epic_result;
	auto skill_collection = epic::Singleton<MetaManager>()->collection<skill_meta::container>("skill");

	for (auto skillKey : unequipSkillIds)
	{
		auto it = skill_collection->infos.find(skillKey.skillMetaId);
		m_skill_attachment_manager->removeParameterAttachment(skillKey);
		NAMED_DEBUG("logicunit.equip", "### remove stat:{}, {}", skillKey.equipItemId, skillKey.skillMetaId);
	}

	NAMED_DEBUG("logicunit.equip", "ALL: {}", m_stat_manager->toStatString());
	return epic_result.SetOk();
}




void LogicUnit::onAttachSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment)
{
#ifdef ITEM_EQUIP_SKILL
	switch (skill_attachment->m_buff_meta_data.parameterType)
	{
	case meta_define::StatType_e::Hp:
	{
		// HP를 늘릴때 -> current_hp 처리
		// HP를 줄일때 -> current_hp max 처리
		m_stat_manager->attach(skill_attachment);
	}
	break;
	case meta_define::StatType_e::MoveSpeed:
	{
		float value = static_cast<float_t>(m_mobileunit_meta_data.runSpeed + skill_attachment->m_skill_attachment_meta_data.parameterValue);
		m_move_speed = value;
		changeUnitSpeed(value);
		m_stat_manager->attach(skill_attachment);
	}
	break;
	default:
		m_stat_manager->attach(skill_attachment);
	}

#else
	epic::Singleton<BattleManager>()->attachSkillBuff(shared_from_this(), skill_attachment->m_buff_meta_data, skill_attachment->m_skill_attachment_meta_data.parameterValue);
#endif // ifdef ITEM_EQUIP_SKILL

	skill_attachment->m_signal_skill_detachment.connect(boost::bind(&LogicUnit::onDetachSkillAttachment, this, _1));
	skill_attachment->m_signal_skill_attachemnt_tick.connect(boost::bind(&LogicUnit::onTickSkillAttachment, this, _1));

	switch (skill_attachment->m_buff_meta_data.buffFunction)
	{
	case buff_meta::BuffFunction_e::Lock:
	{
		m_lock_state = true;
	}
	break;
	case buff_meta::BuffFunction_e::Knockdown:
	{
		m_lock_state = true;
	}
	break;
	}

	if (skill_attachment->m_buff_meta_data.notifiable)
	{
		epic_msg_buff::notify_attach notify;
		notify.__set_skillMetaId(skill_attachment->m_skill_meta_id);
		notify.__set_buffMetaId(skill_attachment->m_buff_meta_data.meta_id);
		notify.__set_unitInstantId(*m_instantId);

		areaBroadcast(MessageToEpicPacket(notify));
	}
}

void LogicUnit::onDetachSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment)
{
#ifdef ITEM_EQUIP_SKILL
	switch (skill_attachment->m_buff_meta_data.parameterType)
	{
	case meta_define::StatType_e::Hp:
	{
		int32_t hp = m_stat_manager->detach(skill_attachment->m_skill_meta_id, skill_attachment->m_sequence_id);
	}
	break;
	case meta_define::StatType_e::MoveSpeed:
	{
		m_move_speed = static_cast<float_t>(m_mobileunit_meta_data.runSpeed);
		changeUnitSpeed(m_move_speed);
		m_stat_manager->detach(skill_attachment->m_skill_meta_id, skill_attachment->m_sequence_id);
	}
	break;
	default:
		m_stat_manager->detach(skill_attachment->m_skill_meta_id, skill_attachment->m_sequence_id);
	}
	//NAMED_DEBUG("logicunit.equip", "  = detach {}:{}", skill_attachment->m_buff_meta_data.buffName, skill_attachment->m_skill_attachment_meta_data.parameterValue);
#else
	epic::Singleton<BattleManager>()->detachSkillBuff(shared_from_this(), skill_attachment->m_buff_meta_data);
#endif

	switch (skill_attachment->m_buff_meta_data.buffFunction)
	{
	case buff_meta::BuffFunction_e::Lock:
	{
		m_lock_state = false;
	}
	break;
	case buff_meta::BuffFunction_e::Knockdown:
	{
		m_lock_state = false;
	}
	}

	if (skill_attachment->m_buff_meta_data.notifiable)
	{
		epic_msg_buff::notify_detach notify;
		notify.__set_skillMetaId(skill_attachment->m_skill_meta_id);
		notify.__set_buffMetaId(skill_attachment->m_buff_meta_data.meta_id);
		notify.__set_unitInstantId(*m_instantId);

		areaBroadcast(MessageToEpicPacket(notify));
	}
}

void LogicUnit::onTickSkillAttachment(boost::shared_ptr<SkillAttachment> skill_attachment)
{
	//파라미터에 대한 계산 후 클라에 전송 param value를 전송
#ifdef ITEM_EQUIP_SKILL
	auto value = static_cast<double>(m_stat_manager->attach(skill_attachment));
#else
	auto value = epic::Singleton<BattleManager>()->attachSkillBuff(shared_from_this(), skill_attachment->m_buff_meta_data, skill_attachment->m_skill_attachment_meta_data.parameterValue);
#endif

	if (skill_attachment->m_buff_meta_data.notifiable)
	{
		epic_msg_buff::notify_tick notify;
		notify.__set_skillMetaId(skill_attachment->m_skill_meta_id);
		notify.__set_buffMetaId(skill_attachment->m_buff_meta_data.meta_id);
		notify.__set_unitInstantId(*m_instantId);

		notify.__set_value(value);

		areaBroadcast(MessageToEpicPacket(notify));
	}
}

/**
	@author: duragon
	@data: 2016/4/11
	@desc: 현재는 스킬을 찾아서 있으면 사용, 없으면 Add를 해주고 잇는데,
			무기 스킬이면 무기종속으로 관리
			캐릭터 스킬이면 캐릭터 종속으로 관리 필요
			스킬 레벨 관리도 필요
	@param 
*/
boost::shared_ptr<Skill> LogicUnit::takeAndAddSkill(int32_t skill_meta_id)
{
	auto skill = m_skill_manager.takeSkill(skill_meta_id);
	if (!skill)
	{
		std::vector<int32_t> skill_meta_ids;
		skill_meta_ids.push_back(skill_meta_id);
		//m_skill_manager.addSkill(skill_meta_ids, shared_from_this());
		m_skill_manager.addSkill(skill_meta_ids, this);
		skill = m_skill_manager.takeSkill(skill_meta_id);
	}
	return skill;
}


void LogicUnit::update(int32_t dt)
{
	if (m_dead || !m_spawned)
	{
		return;
	}
	m_skill_manager.update(dt);
	m_skill_attachment_manager->update(dt);

	m_deleta_time = dt;

	m_skill_begin_time += dt;
	if (m_ai_spawn_ready)
	{
		m_ai_spawn_ready_time += dt;
		if (m_ai_spawn_ready_time > 300)
		{
			m_ai_spawn_ready = false;
			m_enable_ai_state = true;
			m_ai_spawn_ready_time = 0;
		}
	}

	updateStateTimer(dt);
	increase_hp(dt); /// fixme. increase hp

	// Update Crowd Agent
	if (this->m_crowd_agent && this->m_crowd_agent->m_manager)
	{
		CrowdManager* manager = this->m_crowd_agent->m_manager;
		if (manager->m_agent_states.size() >= m_crowd_agent->m_manager_index + 1)
		{
			m_unitPosition.x = manager->m_agent_states[m_crowd_agent->m_manager_index].npos[0];
			m_unitPosition.y = manager->m_agent_states[m_crowd_agent->m_manager_index].npos[1];
			m_unitPosition.z = manager->m_agent_states[m_crowd_agent->m_manager_index].npos[2];
		}
	}

	// Update AI 
	if (m_nodes.empty() || m_lock_state)
	{
		return;
	}
	if (m_enable_ai_state)
	{
		m_ai_elapsed += dt;

		if (m_process_hit_skill.update(dt))
		{
			//NAMED_DEBUG("logicunit.ai", " --- hit call");
			hitSkill(m_process_hit_skill.m_hit_skill.lock());
		}

		if (m_ai_elapsed > m_ai_next_tic)
		{
			m_ai_next_tic = MONSTER_NORMAL_UPDATE;	// patrol reset
			m_rootNode.tick();

			m_ai_elapsed = 0;
			m_ai_patrol_find_tic = 0;
		}
		else if (m_enable_patrol && m_mobileunit_meta_data.attackType == mobileunit_meta::UnitAttackType_e::ActiveAttack)
		{
			m_ai_patrol_find_tic += dt;
			if (m_ai_patrol_find_tic > MONSTER_PATROL_SEARCH)	// partol중 search
			{
				m_ai_patrol_find_tic = 0;
				findTarget(m_findtarget_type);
			}
		}
	}

}

void LogicUnit::updateStateTimer(int32_t delta_time)
{
	if (m_skillstate_timer > 0)
	{
		m_skillstate_timer -= delta_time;
		if (m_skillstate_timer < 0)
		{
			unsetPlayStateTimer();
		}
	}
}

epic::Result LogicUnit::equipVehicle(uint32_t item_db_id, int32_t vehicle_id)
{
	epic::Result epic_result;
	m_vehicle_id = vehicle_id;
	changeUnitSpeed(VEHICLE_SPEED);
	return epic_result;
}
epic::Result LogicUnit::unequipVehicle(uint32_t item_db_id, int32_t vehicle_id)
{
	epic::Result epic_result;
	m_vehicle_id = 0;
	changeUnitSpeed(0);
	return epic_result;
}
int32_t LogicUnit::getVehicle()
{
	return m_vehicle_id;
}




bool LogicUnit::checkPatrolPossible()
{
	auto logic_area = m_logic_area.lock();
	auto target = m_target_unit.lock();

	if (!isUnitType(unit_meta::UnitType_e::Monster))
	{
		m_enable_patrol = false;
	}
	else if (!logic_area)
	{
		m_enable_patrol = false;
	}
	else if (logic_area->m_area_meta_data.type != epic_define::AreaType_e::Field)
	{
		m_enable_patrol = false;
	}
	else if (target)
	{
		m_enable_patrol = false;
	}
	else if (m_back_out)
	{
		m_enable_patrol = false;
	}
	else
	{
		m_enable_patrol = true;
	}
	return m_enable_patrol;
}

bool LogicUnit::enterPatrol()
{
	auto logic_area = m_logic_area.lock();
	if (!logic_area || m_enable_patrol != true)
	{
		m_enable_patrol = false;
		return m_enable_patrol;
	}

	m_enable_patrol = true;
	auto nav_mesh_manager = logic_area->m_nav_mesh_manager.lock();
	if (nav_mesh_manager)
	{
		float dist = 0;
		glm::vec3 spawn_pos, result_pos;
		spawn_pos.x = static_cast<float_t>(m_spawnPosition.x);
		spawn_pos.y = static_cast<float_t>(m_spawnPosition.y);
		spawn_pos.z = static_cast<float_t>(m_spawnPosition.z);

		int32_t random_action = RandomInt(0, 100);
		if (random_action < 50)	// 30% 제자리
		{
			return true;
		}

		//result_pos = nav_mesh_manager->takeRandomPosition(spawn_pos, 0.6f);	// 0.6이면 단위가?
		result_pos = nav_mesh_manager->computeRandomPosition(spawn_pos, 3.0f);	// 3m

		dist = glm::distance(unitPosition(), spawnPosition());

		m_ai_next_tic = MONSTER_PATROL_UPDATE;
		moveToTarget(result_pos, true, unit_meta::AniType_e::WalkFront);

		//NAMED_DEBUG("logicunit.ai", "{}: ----- patrol call dist {}", instantId(), dist);
		return true;
	}
	return false;
}

bool LogicUnit::findable()
{
	// M3 하드코딩 보호 퀘스트일때는 타겟을 바꾸지 않는다.
	// M3이후에 삭제
	if (m_target_locked)
	{
		return false;
	}

	if (m_back_out)
	{
		return false;
	}

	return true;
}

bool LogicUnit::findTarget(meta_define::TargetType_e::type team)
{
	m_findtarget_type = team;

	if (!findable())
	{
		return false;
	}

	auto logic_area = m_logic_area.lock();
	auto target_unit = m_target_unit.lock();
	if (target_unit && target_unit->m_dead == false)
	{
		return true;
	}
	if (m_mobileunit_meta_data.attackType == mobileunit_meta::UnitAttackType_e::PassiveAttack)
	{
		return false;
	}

	//현재 거리에 맞는 타겟을 찾고 스킬 그룹을 선택한다.
	switch (team)
	{
	case meta_define::TargetType_e::_BEGIN:
	case meta_define::TargetType_e::Enemy:
	{
		if (checkTargetAttackable(target_unit) == false)
		{
			m_target_unit.reset();
		}
		auto unit = logic_area->m_unit_manager->takeTargetWithInDistance(shared_from_this(), team, static_cast<float>(this->m_mobileunit_meta_data.searchDistance));
		if (unit)
		{
			if (!unit->m_spawned)
			{
				return false;
			}
			m_target_unit = unit;
			m_destPosition = unit->m_unitPosition;
			//NAMED_DEBUG("logicunit.ai", "{}: ----- find target : findTarget function area : {}", instantId(), m_mobileunit_meta_data.searchDistance);
			return true;
		}
	}
	break;
	}
	return false;
}

bool LogicUnit::checkTargetDistance(glm::vec3 targetPosition)
{
	auto unit_distance = glm::distance(unitPosition(), targetPosition);
	if (unit_distance < m_mobileunit_meta_data.searchDistance)
	{
		return true;
	}
	return false;
}

bool LogicUnit::checkTargetAttackable(std::shared_ptr<LogicUnit> target)
{
	if (target)
	{
		if (target->m_dead || target->getPlayState() > meta_define::UnitPlayState_e::NonAttacked)
		{
			return false;
		}
		return true;
	}
	return false;
}



bool LogicUnit::hasTarget(meta_define::TargetType_e::type team)
{
	switch (team)
	{
	case meta_define::TargetType_e::_BEGIN:
	case meta_define::TargetType_e::Enemy:
	{
		auto target = m_target_unit.lock();
		if (target) //이미 타겟이 있다면 true를 리턴한다.
		{
			// 퀘스트에서 NPC 방어타입의 경우 NPC를 MOB이 공격해야 한다. => targetType를 NPC 추가 필요
			if (!target->isUnitType(unit_meta::UnitType_e::Pc) && !target->m_spawned) //나중에 PVP AI 구현에서 Pc는 삭제해야한다.
			{
				//LOG_INFO("not targeted unit : findTarget function");
				return false;
			}

			if (checkTargetDistance(target->unitPosition()))
			{
				return true;
			}
			else
			{
				resetTarget();
				return false;
			}
		}
		return false;
	}
	break;
	}
	//NAMED_DEBUG("logicunit.ai", "not targeted unit : findTarget team type:{}", team);
	return false;
}


/**
	@author: duragon
	@data: 2016/4/21
	@desc: moveToTarget 상태에서만 사용
	@param 
*/
bool LogicUnit::moveToTarget(bool checkTarget /*= false*/, bool sendBroadcast /*= false*/)
{
	if (isUnitType(unit_meta::UnitType_e::Gimmick) || isUnitType(unit_meta::UnitType_e::Prop))
	{
		return false;
	}

	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : moveToTarget function");
		return false;
	}
	auto nav_manager = logic_area->m_nav_mesh_manager.lock();
	if (!nav_manager)
	{
		LOG_ERROR("not nav manager : moveToTarget function");
		return false;
	}
	if (!m_crowd_agent)
	{
		LOG_ERROR("[moveToTarget] m_crowd_agent null ptr");
		return false;
	}

	int32_t USE_ENEMY_FRONT = 0;
	if (checkTarget)
	{
		auto target_unit = m_target_unit.lock();
		if (target_unit)
		{
			if (USE_ENEMY_FRONT)
			{
				auto direction = epic::takeTargetDir(unitPosition(), target_unit->m_unitPosition);
				m_destPosition = epic::addVector(target_unit->m_unitPosition, -direction);
			}
			else
			{
				m_destPosition = target_unit->m_unitPosition;
			}
		}
	}

	glm::vec3 dest_pos, source_pos;
	float_t distance = glm::distance(unitPosition(), destPosition());

	rcnNavmeshPoint navPoint;
	if (!m_crowd_agent || !m_crowd_agent->m_manager)
	{
		LOG_ERROR("not agent created : moveToTarget function");
		return false;
	}
	CrowdManager* manager = m_crowd_agent->m_manager;
	if (manager->m_agent_states.size() < m_crowd_agent->m_manager_index + 1)
	{
		return false;
	}

	dest_pos.x = static_cast<float_t>(m_destPosition.x);
	dest_pos.y = static_cast<float_t>(m_destPosition.y);
	dest_pos.z = static_cast<float_t>(m_destPosition.z);

	dtStatus status = nav_manager->nearestPoint(dest_pos, &navPoint);
	if (dtStatusFailed(status))
	{
		LOG_ERROR("----- nav_manager->nearestPoint Fail dest:{},{},{}", dest_pos.x, dest_pos.y, dest_pos.z);
		return false;
	}
	if (navPoint.polyRef == 0)
	{
		LOG_ERROR("----- nav_manager->nearestPoint navPoint.polyRef Fail");
		return false;
	}
	m_crowd_agent->m_manager->dtcRequestMoveTarget(m_crowd_agent->m_manager->m_root, this->m_crowd_agent->m_manager_index, navPoint);

	m_destPosition.x = navPoint.point[0];
	m_destPosition.y = navPoint.point[1];
	m_destPosition.z = navPoint.point[2];

	if (sendBroadcast)
	{
		epic_msg_area::MoveInfo moveinfo_output;
		setNotifyMoveUnit(unit_meta::AniType_e::Run, moveinfo_output);
		addUnitMoveMsg(moveinfo_output);

		NAMED_DEBUG("logicunit.move", "{}: ----- moveToTarget broad {}:{} to {}", instantId(), m_unit_meta_data.meta_name, epic::ToString(m_unitPosition), epic::ToString(m_destPosition));
		return true;
	}
	NAMED_DEBUG("logicunit.move", "{}: ----- moveToTarget {}:{} to {}", instantId(), m_unit_meta_data.meta_name, epic::ToString(m_unitPosition), epic::ToString(m_destPosition));

	return true;
}



bool LogicUnit::moveToTarget(glm::vec3 dest_position, bool notify, unit_meta::AniType_e::type ani_type)
{
	if (isUnitType(unit_meta::UnitType_e::Gimmick) || isUnitType(unit_meta::UnitType_e::Prop))
	{
		return false;
	}
	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : moveToTarget function");
		return false;
	}
	auto nav_manager = logic_area->m_nav_mesh_manager.lock();
	if (!nav_manager)
	{
		LOG_ERROR("not nav manager : moveToTarget dest function");
		return false;
	}

	if (ani_type == unit_meta::AniType_e::Run)
	{
		changeUnitSpeed(static_cast<float_t>(m_mobileunit_meta_data.runSpeed));
	}
	else if (ani_type == unit_meta::AniType_e::WalkFront)
	{
		changeUnitSpeed(static_cast<float_t>(m_mobileunit_meta_data.walkSpeed));
	}

	glm::vec3 dest_pos, source_pos;
	rcnNavmeshPoint navPoint;
	
	if (!m_crowd_agent || !m_crowd_agent->m_manager)
	{
		LOG_ERROR("not agent created : moveToTarget function");
		return false;
	}

	CrowdManager* manager = m_crowd_agent->m_manager;

	if (manager->m_agent_states.size() < m_crowd_agent->m_manager_index + 1)
	{
		return false;
	}

	dtStatus status = nav_manager->nearestPoint(dest_position, &navPoint);

	if (dtStatusFailed(status))
	{
		return false;
	}
	if (navPoint.polyRef == 0)
	{
		return false;
	}
	//nav_manager->m_crowd_manager->dtcResetMoveTarget(nav_manager->m_crowd_manager->m_root, this->m_crowd_agent->m_manager_index);
	//nav_manager->m_crowd_manager->dtcRequestMoveTarget(nav_manager->m_crowd_manager->m_root, this->m_crowd_agent->m_manager_index, navPoint);
	m_crowd_agent->m_manager->dtcRequestMoveTarget(m_crowd_agent->m_manager->m_root, m_crowd_agent->m_manager_index, navPoint);

	m_destPosition.x = navPoint.point[0];
	m_destPosition.y = navPoint.point[1];
	m_destPosition.z = navPoint.point[2];

	if (notify)
	{
		epic_msg_area::MoveInfo moveinfo_output;
		setNotifyMoveUnit(ani_type, moveinfo_output);
		addUnitMoveMsg(moveinfo_output);
	}
	//LOG_DEBUG("----- moveToTarget dest_position : {} by {} to {}", m_unit_meta_data.meta_name, ani_type==unit_meta::AniType_e::Run?"Run":"Walk", notify?"send":"alone");

	return true;
}


/**
	@author: duragon
	@data: 2016/4/21
	@desc: just move width speed
	@param 
*/
bool LogicUnit::moveToTarget(glm::vec3 dest_position, float move_speed)
{
	if (isUnitType(unit_meta::UnitType_e::Gimmick) || isUnitType(unit_meta::UnitType_e::Prop))
	{
		return false;
	}
	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : moveToTarget function");
		return false;
	}
	auto nav_manager = logic_area->m_nav_mesh_manager.lock();
	if (!nav_manager)
	{
		LOG_ERROR("not nav manager : moveToTarget dest function");
		return false;
	}
	if (!m_crowd_agent || !m_crowd_agent->m_manager)
	{
		LOG_ERROR("not agent created : moveToTarget function");
		return false;
	}

	glm::vec3 dest_pos, source_pos;
	rcnNavmeshPoint navPoint;
	CrowdManager* manager = m_crowd_agent->m_manager;

	changeUnitSpeed(move_speed);

	if (manager->m_agent_states.size() < m_crowd_agent->m_manager_index + 1)
	{
		LOG_ERROR("moveToTarget m_agent_states or m_crowd_agent->m_manager_index Error");
		return false;
	}

	dtStatus status = nav_manager->nearestPoint(dest_position, &navPoint);

	if (dtStatusFailed(status))
	{
		LOG_ERROR("moveToTarget dtStatus Failed");
		return false;
	}
	if (navPoint.polyRef == 0)
	{
		LOG_ERROR("moveToTarget polyRef == 0");
		return false;
	}
	m_crowd_agent->m_manager->dtcRequestMoveTarget(m_crowd_agent->m_manager->m_root, this->m_crowd_agent->m_manager_index, navPoint);

	m_destPosition.x = navPoint.point[0];
	m_destPosition.y = navPoint.point[1];
	m_destPosition.z = navPoint.point[2];

	//LOG_DEBUG("----- moveToTarget dest_position : {} by {} to {}", m_unit_meta_data.meta_name, ani_type==unit_meta::AniType_e::Run?"Run":"Walk", notify?"send":"alone");

	return true;
}


bool LogicUnit::approachStart()
{
	auto skill = m_skill_manager.m_current_skill.lock();
	if (!skill)
	{
		return false;
	}
	auto target_unit = m_target_unit.lock();
	if (!target_unit)
	{
		m_skill_manager.clearCurrentSkill();
		return false;
	}

	m_destPosition = target_unit->m_unitPosition;
	auto move_distance = glm::distance(unitPosition(), destPosition()) - static_cast<float_t>(skill->m_skill_meta_data.attackDistance);
	auto direction = epic::takeTargetDir(unitPosition(), destPosition());
	auto dest_pos = unitPosition() + direction * move_distance;

	if (move_distance > APPROACH_ERROR_BOUND)
	{
		skill->m_skill_state = skill_meta::SkillState_e::Approach;
		moveToTarget(dest_pos, true, unit_meta::AniType_e::Run);
		//NAMED_DEBUG("logicunit.ai", "{}: ----- approch skill {} : move to dest dist:{}", instantId(), skill->m_skill_meta_data.meta_name, move_distance);
		return true;
	}
	return false;
}

bool LogicUnit::approachUpdate()
{
	auto skill = m_skill_manager.m_current_skill.lock();
	if (!skill)
	{
		return false;
	}
	auto target_unit = m_target_unit.lock();
	if (!target_unit)
	{
		m_skill_manager.clearCurrentSkill();
		return false;
	}

	m_destPosition = target_unit->m_unitPosition;
	auto target_distance = glm::distance(unitPosition(), destPosition());
	auto move_distance = glm::distance(unitPosition(), destPosition()) - static_cast<float_t>(skill->m_skill_meta_data.attackDistance);
	auto direction = epic::takeTargetDir(unitPosition(), destPosition());
	auto dest_pos = unitPosition() + direction * move_distance;

	if (move_distance < APPROACH_ERROR_BOUND)
	{
		skill->m_skill_state = skill_meta::SkillState_e::ApproachEnd;
		//NAMED_DEBUG("logicunit.ai", "----- check approch skill approachEnd: {}", skill->m_skill_meta_data.meta_name);
		return true;
	}

	// Mob animation을 intergrationMove로 변경 필요
	//LOG_INFO("----- approaching: {}, dist:{}, {}", skill->m_skill_meta_data.meta_name, move_distance, target_distance);
	moveToTarget(dest_pos, true, unit_meta::AniType_e::Run);
	return false;
}


void LogicUnit::changeUnitSpeed(float speed)
{
	if (speed <= 0)
	{
		m_crowd_agent_param.maxSpeed = (float)m_mobileunit_meta_data.runSpeed; // default
		m_crowd_agent_param.maxAcceleration = 0;
	}
	else
	{
		m_crowd_agent_param.maxSpeed = speed;
	}

	if (nullptr != m_crowd_agent)
	{
		m_crowd_agent->m_manager->m_root->updateAgentParameters(m_crowd_agent->m_manager_index, &m_crowd_agent_param);
	}
}

bool LogicUnit::skillUsable()
{
	auto current_skill = m_skill_manager.m_current_skill.lock();
	if (current_skill)
	{
		if (current_skill->m_skill_state == skill_meta::SkillState_e::Approach)
		{
			if (approachUpdate())
			{
				return true;
			}
			return true;
		}
		if (skill_meta::SkillState_e::Looping == current_skill->m_skill_state)
		{
			m_skill_begin_time = 0;
			return true;
		}
	}

	if (m_next_skill_usable_time > m_skill_begin_time)
	{
		return false;
	}
	m_skill_begin_time = 0;
	return true;
}

bool LogicUnit::useSkill(skill_meta::AttackType_e::type skill_type)
{
	//setAIState("Use Skill");

	if (!skillUsable())
	{
		return false;
	}

	auto skill = selectSkill(skill_type);
	if (!skill)
	{
		return false;
	}

	if (skill->m_skill_state == skill_meta::SkillState_e::Approach)
	{
		// 목표방향은 skillUsable() 또는 selectSkill()에서 설정
		return true;
	}
	if (skill->hasCastingTime())
	{
		// cast skill 이후 shotskill로 이어지는 접점이 없음.
		castSkill(skill);
	}
	else
	{
		shotSkill(skill);
	}
	//LOG_DEBUG("----- useSkill dest_position : {}", skill->m_skill_meta_data.meta_name);
	setNextSkillUsableTime();
	return true;
}

void LogicUnit::hitByUserSkill()
{
	// escape patrol,
	if (m_enable_patrol)
	{
		m_enable_patrol = false;
	}

	m_ai_next_tic = MONSTER_ATACKED_DELAY;	// 피격 Animation이 나오는 시간을 충분히 줘야 한다.

	// cancel skill
	m_process_hit_skill.clear();
	m_skill_manager.clearCurrentSkill();
}

// AI
void LogicUnit::shotSkill(boost::shared_ptr<Skill> skill)
{
	LOG_DEBUG("{}: {}:::   shotSkill {}:{}", instantId(), m_unit_meta_data.meta_name, skill->m_skill_meta_data.meta_id, skill->m_skill_meta_data.meta_name);

	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : useSkill function");
		return;
	}
	auto target = m_target_unit.lock();
	if (!target)
	{
		LOG_ERROR("not target : useSkill fail");
		return;
	}

	m_destPosition = target->m_unitPosition;
	m_direction = logic_area->m_unit_manager->takeTargetDir(m_unitPosition, m_destPosition);
	m_angle = epic::rotationAngle(m_direction);

	float event_move = static_cast<float_t>(skill->m_skill_meta_data.eventMove);
	if (event_move != 0.0f)
	{
		glm::vec3 destPosition;
		switch (skill->m_skill_meta_data.skillDirection)
		{
		//case skill_meta::SkillDirection_e::_BEGIN:
		case skill_meta::SkillDirection_e::FRONT:
		case skill_meta::SkillDirection_e::BACK:
			destPosition = unitPosition() + (m_direction * event_move);//이동 방향에 따라 방향 백터를 곱해줘야함 ex) x (1, 0, 0) 백터
			break;
		case skill_meta::SkillDirection_e::RIGHT:
		case skill_meta::SkillDirection_e::LEFT:
			glm::vec3 axis_vector = glm::cross(m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
			destPosition = unitPosition() + (glm::normalize(axis_vector) * -event_move);//이동 방향에 따라 방향 백터를 곱해줘야함 ex) x (1, 0, 0) 백터
			break;
		}

		float move_speed = m_mobileunit_meta_data.runSpeed ;
		m_destPosition = epic::toVector<epic_define::UnitPosition>(destPosition);	// 이동스킬의 경우 이동 위치까지 움직임
		if (skill->m_skill_meta_data.shotTime > 0) 
		{
			move_speed = float(skill->m_skill_meta_data.eventMove*1000 / skill->m_skill_meta_data.shotTime);
			move_speed = (move_speed < 1.0f) ? 1.0f : move_speed;
		}
		moveToTarget(destPosition, move_speed);
		//LOG_DEBUG("ShotSkill Move current:{}, speed:{}", epic::ToString(m_unitPosition), move_speed);
		//LOG_DEBUG("ShotSkill Move dest:{}", epic::ToString(destPosition));
	}

	m_unitPosition.angle = m_angle;
	epic_msg_skill::notify_shot notify_shot_skill;
	epic_msg_skill::notify_hit notify_hit_skill;

	notify_shot_skill.__set_attackerPosition(m_unitPosition);
	notify_shot_skill.__set_attackInstantId(this->instantId());
	notify_shot_skill.__set_skillMetaId(skill->m_skill_meta_id);

	notify_hit_skill.__set_attackInstantId(this->instantId());
	notify_hit_skill.__set_skillMetaId(skill->m_skill_meta_id);


	epic_define::UnitPosition direction;
	direction.x = m_direction.x;
	direction.y = m_direction.y;
	direction.z = m_direction.z;
	direction.angle = 0;
	notify_shot_skill.__set_direction(direction);

	//LOG_DEBUG("   shot Position {}", epic::ToString(m_unitPosition));
	//LOG_DEBUG("   shot direction {}", epic::ToString(direction));

	if (event_move != 0.0f)
	{
		notify_shot_skill.__set_destPos(m_destPosition);
	}
	else
	{
		notify_shot_skill.__set_destPos(m_unitPosition);
	}

	areaBroadcast(MessageToEpicPacket(notify_shot_skill));		// Broadcast ShotSkill

	skill->shotSkill();

	//if (skill->m_skill_meta_data.attackTypes == skill_meta::AttackType_e::Move)
	if (skill->m_skill_meta_data.skillType == skill_meta::SkillType_e::AI_Move)
	{
		return;
	}
	//else if (skill->m_skill_meta_data.skillType == skill_meta::SkillType_e::AI_Far)
	//{
	//	// Client compute skill damage and send tell_hit_by_mob
	//	m_skill_attachment_manager->attach(skill->m_skill_meta_id, skill->m_skill_meta_data.shotSkillAttachment);
	//	return;
	//}

	//////////////////////////////////////////////////////////////////////////
	//
	// mob active skill damage compute
	//
	m_skill_attachment_manager->attach(skill->m_skill_meta_id, skill->m_skill_meta_data.shotSkillAttachment);


	//////////////////////////////////////////////////////////////////////////
	//
	// 이 부분은 추후에 skill 내부에 시간값과 LogicUnit의 상태를 통해서 피격이 발생하는 시점에 계산되어 Broadcast 하도록 한다.
	//
	skill->m_attack_index = 0;	// 시작
	m_process_hit_skill.set(skill);
	//hitSkill(skill);	

	/*
	//155: double range //적용 범위
	//	156 : double angle //적용 각도
	//	157 : i16 maxTargetCount //최대 스킬 적용 대상, 0 범위내 모두

	//=========================================================================
	// 공격스킬의 경우 공격 범위내에 있는 피격대상을 계산하도록 한다.
	// 1. 근거리 스킬의 경우 -> 즉시 데미지 계산 및 전달
	// 2. 원거리 스킬의 경우 -> 클라이언트에서 판정후 서버에 전달하도록 한다.

	glm::vec3 attack_center_pos = m_direction*(float)skill->m_skill_meta_data.attackDistance + unitPosition();
	//std::vector<std::shared_ptr<LogicUnit>> targets = logic_area->m_unit_manager->takeTargetWithInDistanceCircleList(skill->m_skill_meta_data.attackDistance, shared_from_this(), skill->m_skill_meta_data.targetType, attack_pos, skill->m_skill_meta_data.attackRange, skill->m_skill_meta_data.maxTargetCount);
	std::vector<std::shared_ptr<LogicUnit>> targets = logic_area->m_unit_manager->takeTargetWithInDistanceCircleList(shared_from_this(), skill->m_skill_meta_data.targetType, attack_center_pos, skill->m_skill_meta_data.attackRange, skill->m_skill_meta_data.maxTargetCount);

	if (skill->m_skill_meta_data.skillType == skill_meta::SkillType_e::AI_Casting)
	{
		if (m_target_unit.lock())
		{
			targets.push_back(m_target_unit.lock());
		}
	}
	
	epic_msg_skill::HitInfo hit_info;
	float skill_push_back = skill->takePushDistance();
	boost::shared_ptr<SkillAttachment> skill_attachment;
	for (auto target : targets)
	{
		glm::vec3 hit_direction;
		glm::vec3 hit_dest_position = target->unitPosition();
		
		hit_direction = epic::takeTargetDir(m_unitPosition, target->unitPosition());

		hit_info.__set_defenderInstantId(target->instantId());
		hit_info.__set_hitPotision(target->m_unitPosition);
		if (skill_push_back > 0.01f)
		{
			hit_dest_position += (-skill_push_back * hit_direction); // 맞아서 넉백되는 스킬이면 뒤로 밀어줘야 함.
			target->moveToTarget(hit_dest_position, false);
			//LOG_INFO("   hit knockback distance:{} move {} to {}", skill_push_back, epic::ToString(target->unitPosition()), epic::ToString(hit_dest_position));
			LOG_INFO("   hit knockback distance:{} ", skill_push_back);
		}
		hit_info.__set_destPosition(target->m_unitPosition);	

		
		//notify_shot_skill.__set_hitInfos(hit_infos);
		if (false == target->isUnitType(unit_meta::UnitType_e::Prop) && false == target->isUnitType(unit_meta::UnitType_e::Gimmick))
		{
			target->m_skill_attachment_manager->attach(skill->m_skill_meta_id, skill->m_skill_meta_data.hitSkillAttachment, skill_attachment);
		}
		if (target->isUnitType(unit_meta::UnitType_e::BattleNpc))
		{
			target->m_target_unit = shared_from_this();
		}

		// process damage
		skill_meta::SkillDamage result_damage;
		epic::Singleton<BattleManager>()->skillDamage(skill, shared_from_this(), target->getStat(meta_define::StatType_e::Defense), result_damage);

		hit_info.__set_damage(result_damage.damage);
		hit_info.__set_critical(result_damage.critical);

		target->m_curent_hp = target->m_curent_hp - result_damage.damage;
		hit_info.__set_currentHp(target->m_curent_hp);

		if (target->m_curent_hp <= 0 && false == target->m_dead)
		{
			onKillTarget(target);
			target->dead();
			m_target_unit.reset();
			LOG_INFO("   = AI_unit {} kill {}...", m_unit_meta_data.meta_name, target->m_unit_meta_data.meta_name);
		}

		notify_hit_skill.hitInfos.push_back(hit_info);
	}

	if (notify_hit_skill.hitInfos.size() > 0)
	{
		areaBroadcast(MessageToEpicPacket(notify_hit_skill));
	}
	*/
}



/**
	@author: duragon
	@data: 2016/4/20
	@desc: 공격 데미지 정보 설정
	@param 
*/
void LogicUnit::hitSkill(boost::shared_ptr<Skill> skill)
{
	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : useSkill function");
		return;
	}
	if (!skill)
	{
		LOG_ERROR("skill is empty : hitSkill function");
		return;
	}

	boost::shared_ptr<SkillAttachment> skill_attachment;
	epic_msg_skill::HitInfo hit_info;
	epic_msg_skill::notify_hit notify_hit_skill;

	notify_hit_skill.__set_attackInstantId(this->instantId());
	notify_hit_skill.__set_skillMetaId(skill->m_skill_meta_id);

	glm::vec3 attack_center_pos = m_direction*(float)skill->takeAttackDistance() + unitPosition();
	//LOG_DEBUG("   hit direction {}", epic::ToString(m_direction));
	//LOG_DEBUG("   position {}", epic::ToString(m_unitPosition));

	auto target = m_target_unit.lock();
	std::vector<std::shared_ptr<LogicUnit>> targets;

	// take Target
	if (skill->takeMaxAttackCount() < 1)
	{
		LOG_ERROR("@@@ hitSkill:: attackTimeLine is Empty");
		m_process_hit_skill.clear();
		return;
	}
	else if ( target && skill->takeTargetCount() == 1)
	{
		// check target is in the attackrange
		auto unit_dist = glm::distance(unitPosition(), target->unitPosition());
		auto dist = glm::distance(attack_center_pos, target->unitPosition());
		if (dist <= skill->takeAttackRange()+ ATTACK_RANGE_MARGIN)
		{
			targets.push_back(target);
		}
		else
		{
			//NAMED_DEBUG("logicunit.ai", "@@@ hitSkill:: target is too far {} / {} - unit dist{}, skill:{}/{}", dist, skill->takeAttackRange() + ATTACK_RANGE_MARGIN, unit_dist, skill->m_attack_index, skill->takeMaxAttackCount());
			m_process_hit_skill.setNext(skill->computeNextHit());
			return;
		}
	}
	else
	{
		targets = logic_area->m_unit_manager->takeTargetWithInDistanceCircleList(shared_from_this(), skill->m_skill_meta_data.targetType, attack_center_pos, skill->takeAttackRange() + ATTACK_RANGE_MARGIN, skill->takeTargetCount());
	}

	// compute damage
	for (auto target : targets)
	{
		glm::vec3 hit_direction;
		glm::vec3 hit_dest_position = target->unitPosition();
		float skill_push_back = skill->takePushDistance();
		hit_direction = epic::takeTargetDir(m_unitPosition, target->unitPosition());

		if (target->getPlayState() > meta_define::UnitPlayState_e::NonHitted)
		{
			LOG_DEBUG("  skip nonhitted state {}:{}", target->instantId(), target->m_mobileunit_meta_data.meta_name);
			continue;
		}

		hit_info.__set_defenderInstantId(target->instantId());
		hit_info.__set_hitPotision(target->m_unitPosition);
		if (skill_push_back >= 0.01f)
		{
			hit_dest_position += (-skill_push_back * hit_direction); // 맞아서 넉백되는 스킬이면 뒤로 밀어줘야 함.

			NAMED_DEBUG("logicunit.ai", "   push target Position {}", epic::ToString(target->m_unitPosition));
			NAMED_DEBUG("logicunit.ai", "   push back distance:{} ", skill_push_back);
			NAMED_DEBUG("logicunit.ai", "   push move dest {}", epic::ToString(hit_dest_position));

			target->moveToTarget(hit_dest_position, 3.0f); //rootmotion check
			hit_info.__set_destPosition( epic::toVector<epic_define::UnitPosition>(hit_dest_position));
		}
		else 
		{
			hit_info.__set_destPosition(target->m_unitPosition);
		}


		if (false == target->isUnitType(unit_meta::UnitType_e::Prop) && false == target->isUnitType(unit_meta::UnitType_e::Gimmick))
		{
			target->m_skill_attachment_manager->attach(skill->m_skill_meta_id, skill->m_skill_meta_data.hitSkillAttachment, skill_attachment);
		}
		if (target->isUnitType(unit_meta::UnitType_e::BattleNpc))
		{
			target->m_target_unit = shared_from_this();
		}

		// process damage
		skill_meta::SkillDamage result_damage;
		epic::Singleton<BattleManager>()->skillDamageAI(skill, shared_from_this(), target->getStat(meta_define::StatType_e::Defense), result_damage);

		hit_info.__set_damage(result_damage.damage );
		hit_info.__set_critical(result_damage.critical);

		target->m_curent_hp = target->m_curent_hp - result_damage.damage;
		hit_info.__set_currentHp(target->m_curent_hp);

		if (target->m_curent_hp <= 0 && false == target->m_dead)
		{
			onKillTarget(target);
			target->dead();
			m_target_unit.reset();
			LOG_INFO("   = AI_unit {} kill {}...", m_unit_meta_data.meta_name, target->m_unit_meta_data.meta_name);
		}

		notify_hit_skill.hitInfos.push_back(hit_info);
	}

	if (notify_hit_skill.hitInfos.size() > 0)
	{
		areaBroadcast(MessageToEpicPacket(notify_hit_skill));
	}

	m_process_hit_skill.setNext(skill->computeNextHit());
}







void LogicUnit::endSkill(boost::shared_ptr<Skill> skill)
{
	auto logic_area = m_logic_area.lock();
	if (!logic_area)
	{
		LOG_ERROR("not logic area : useSkill function");
		return;
	}

	m_direction = logic_area->m_unit_manager->takeTargetDir(m_unitPosition, m_destPosition);

	float_t angle = 0.0f;
	m_angle = epic::rotationAngle(m_direction);

	epic_msg_skill::notify_end notify;
	notify.__set_unitInstantId(this->instantId());
	notify.__set_angle(m_angle);

	// after skilluse position correction
	//NAMED_DEBUG("logicunit.ai", "Skill END:: unit: {} / dest: {}", epic::ToString(m_unitPosition), epic::ToString(m_destPosition));
	
	//areaBroadcast(MessageToEpicPacket(notify));	// Client 처리되지 않음
}

void LogicUnit::resetCurrentSkill(int32_t skill_meta_id)
{
	m_skill_attachment_manager->playExpiredCheck();
}



bool LogicUnit::checkBackOutPossible()
{
	if (!isUnitType(unit_meta::UnitType_e::Monster))
	{
		return false;
	}
	if (this->m_mobileunit_meta_data.sectorDistane < 1)
	{
		return false;
	}
	if (true == m_target_locked)
	{
		return false;
	}

	auto dist = glm::distance(spawnPosition(), unitPosition());

	// 백아웃 진입
	if (m_back_out == false && dist > m_mobileunit_meta_data.sectorDistane )
	{
		//NAMED_DEBUG("logicunit.ai", "{}: ----- backOut call, dist:{} > {}", instantId(), dist, m_mobileunit_meta_data.sectorDistane);
		return true;
	}

	//현재 백아웃 상태에서 스폰위치와의 거리가 1.5미만이면 백아웃 상태를 해제한다.
	if (m_back_out)
	{
		if (dist < 1.5f)
		{
			//NAMED_DEBUG("logicunit.ai", "{}: ----- backOut END:: comback spawnPosition", instantId());
			m_back_out = false;
			return false;
		}
		return true;	// 백아웃 상태 유지
	}

	return false;
}

bool LogicUnit::backOut()
{
	if (m_back_out == true)
	{
		return true;
	}

	resetTarget();

	m_back_out = true;
	m_destPosition = m_spawnPosition;
	moveToTarget(destPosition(), true);
	return true;
}



/**
	@author: duragon
	@data: 2016/4/14
	@desc: nest 보스가 특정 상황에서 사용하는 스킬 정의
			mobileunit_meta::nestCondition
	@param 
*/
bool LogicUnit::checkNestCondition()
{
	if (m_mobileunit_meta_data.unitScale != mobileunit_meta::UnitScaleType_e::Heavy)
	{
		return false;
	}
	return false; 
}



bool LogicUnit::useNestConditionSkill()
{
	return false; 
}






void LogicUnit::setAIState(string_t state_string)
{
	LOG_TRACE("Set AI State : {}", state_string);
	m_ai_state = state_string;
}

// not Used
//bool LogicUnit::checkUseSkillDistance()
//{
//	auto target_unit = m_target_unit.lock();
//	if (!target_unit)
//	{
//		return false;
//	}
//	auto area = m_logic_area.lock();
//	if (!area)
//	{
//		return false;
//	}
//
//	auto unit_distance = glm::distance(unitPosition(), target_unit->unitPosition());
//	m_attack_distance_ok = false;
//
//	for (auto skill_group : m_mobileunit_meta_data.skillGroups)
//	{
//		if (glm::abs(unit_distance) <= skill_group.selectDistance)
//		{
//			m_attack_distance_ok = true;
//			break;
//		}
//	}
//	return m_attack_distance_ok;
//}



void LogicUnit::setNextSkillUsableTime()
{
	int32_t random_range = epic::random(0, (int32_t)m_mobileunit_meta_data.skillInterval);

	auto current_skill = m_skill_manager.m_current_skill.lock();
	if (current_skill)
	{
		if (current_skill->m_skill_meta_data.skillType == skill_meta::SkillType_e::AI_Move)
		{
			m_next_skill_usable_time = current_skill->totalLeftTime();	// 이동스킬
		}
		else
		{
			m_next_skill_usable_time = current_skill->totalLeftTime() + random_range;
		}
	}
	else
	{
		m_next_skill_usable_time = random_range;
	}

	LOG_INFO("next skill usable time:{}", m_next_skill_usable_time);
}

boost::shared_ptr<Skill> LogicUnit::selectSkill(skill_meta::AttackType_e::type skill_type)
{
	boost::shared_ptr<Skill> skill = boost::shared_ptr<Skill>();

	auto target_unit = m_target_unit.lock();
	if (checkTargetAttackable(target_unit) == false)
	{
		LOG_ERROR("selectSkill::target_unit is null or nonAttackable");
		m_skill_manager.clearCurrentSkill();
		return skill;
	}

	auto current_skill = m_skill_manager.m_current_skill.lock();
	if (current_skill)
	{
		if (current_skill->m_skill_state == skill_meta::SkillState_e::Approach)
		{
			LOG_INFO("  use Approach skill: {}, {}", current_skill->m_skill_meta_id, current_skill->m_skill_meta_data.meta_name);
			return current_skill;
		}
		//루프 중이면 기존 스킬 사용, 접근후스킬사용중이면 기존스킬 사용
		if (current_skill->m_loop_count > 0)
		{
			//LOG_INFO("  use loop skill: {}, loop_count: {}", current_skill->m_skill_meta_id, current_skill->m_loop_count);
			return current_skill;
		}
	}
	else if (hasSkillGroup())
	{
		m_destPosition = target_unit->m_unitPosition;
		auto unit_distance = glm::distance(unitPosition(), destPosition());
		if (unit_distance <= m_mobileunit_meta_data.searchDistance)
		{
			int32_t hp_rate = (m_curent_hp * 100 / getStat(meta_define::StatType_e::Hp));
			//skill = m_skill_manager.takeSkillByDistance(unit_distance, this);
			skill = m_skill_manager.takeSkillByDistance(hp_rate, unit_distance);
			if (skill)
			{
				LOG_INFO("   takeSkillByDistance hp:{}, distance:{} - skill:{}", hp_rate, unit_distance, skill->m_skill_meta_id);
				if (skill->isAssultSkill())
				{
					LOG_INFO("select AssultSkill");
					skill = m_skill_manager.takeSkill(skill->takeAssultSkillMetaId());
					if (!skill)
					{
						return skill;
					}
					skill->m_loop_count = 1;
					m_skill_manager.m_current_skill = skill;
					approachStart();
				}
			}
		}

		if ( !skill || skill->m_skill_meta_id == 0 )
		{
			// 거리에 맞는 스킬을 찾을수 없다면
			LOG_ERROR("selectSkill::takeSkillByDistance fail.skill is null: {}:{}", m_mobileunit_meta_data.meta_id, m_mobileunit_meta_data.meta_name);
			resetTarget();
		}
	}
	else
	{
		// 몬스터가 거리별 스킬이 없을때 스킬타입으로 찾을 이유가 있을까??
		LOG_ERROR("no skill group. mobileunit:{}:{}", m_mobileunit_meta_data.meta_id, m_mobileunit_meta_data.meta_name);
		resetTarget();
	}

	m_skill_manager.m_current_skill = skill;
	return skill;
}

bool LogicUnit::castSkill(boost::shared_ptr<Skill> skill)
{
	auto area = m_logic_area.lock();
	if (!area)
	{
		LOG_ERROR("not logic area : useSkill function");
		return false;
	}

	m_direction = area->m_unit_manager->takeTargetDir(m_unitPosition, m_destPosition);
	m_angle = epic::rotationAngle(m_direction);

	if (skill->castSkill().Ok())
	{
		m_unitPosition.__set_angle(m_angle);
		epic_msg_skill::notify_cast notify_cast_skill;
		notify_cast_skill.__set_skillMetaId(skill->m_skill_meta_id);
		notify_cast_skill.__set_unitInstantId(this->instantId());
		notify_cast_skill.__set_unitPos(m_unitPosition);

		areaBroadcast(MessageToEpicPacket(notify_cast_skill));
	}

	return true;
}

void LogicUnit::setNotifyMoveUnit(unit_meta::AniType_e::type ani_type, _out epic_msg_area::MoveInfo &info)
{
	info.__set_destPosition(m_destPosition);
	info.__set_pos(m_unitPosition);
	if (ani_type == unit_meta::AniType_e::Run)
	{
		info.__set_speed(m_mobileunit_meta_data.runSpeed);
	}
	else if (ani_type == unit_meta::AniType_e::WalkFront)
	{
		info.__set_speed(m_mobileunit_meta_data.walkSpeed);
	}
	info.__set_unitId(instantId());
	info.__set_aniType(ani_type);
	info.__set_unitState(m_client_state);
}

void LogicUnit::areaBroadcast(std::shared_ptr<EpicPacket> epic_packet)
{
	auto logic_area = m_logic_area.lock();

	if (nullptr == logic_area)
	{
		return;
	}

	logic_area->broadcast(epic_packet);
}

void LogicUnit::addUnitMoveMsg(epic_msg_area::MoveInfo& moveinfo)
{
	auto logic_area = m_logic_area.lock();

	if (nullptr == logic_area)
	{
		return;
	}

	logic_area->addMoveMesg(moveinfo);
}

//epic::Result LogicUnit::removeToCrowdAgent()
//{
//	auto logic_area = m_logic_area.lock();
//
//	if (!logic_area)
//	{
//		return epic::Result().SetFail(sformat("[removeToCrowdAgent] logic_area is null"));
//	}
//
//	auto nav_mesh_manager = logic_area->m_nav_mesh_manager.lock();
//	if (!nav_mesh_manager)
//	{
//		return epic::Result().SetFail(sformat("[removeToCrowdAgent] nav_mesg_manager is null"));
//	}
//	if (!m_crowd_agent)
//	{
//		return epic::Result().SetFail(sformat("[removeToCrowdAgent] m_crowd_agent is null"));
//	}
//	nav_mesh_manager->m_crowd_manager->removeAgent(m_crowd_agent);
//	m_crowd_agent = nullptr;
//	return epic::Result().SetOk();
//}


epic::Result LogicUnit::removeToCrowdAgent()
{
	auto logic_area = m_logic_area.lock();

	if (!logic_area)
	{
		return epic::Result().SetFail(sformat("[removeToCrowdAgent] logic_area is null"));
	}

	auto nav_mesh_manager = logic_area->m_nav_mesh_manager.lock();
	if (!nav_mesh_manager)
	{
		return epic::Result().SetFail(sformat("[removeToCrowdAgent] nav_mesg_manager is null"));
	}
	if (!m_crowd_agent)
	{
		return epic::Result().SetFail(sformat("[removeToCrowdAgent] m_crowd_agent is null"));
	}
	nav_mesh_manager->remove_crowd_agent(m_crowd_agent);
	m_crowd_agent = nullptr;
	return epic::Result().SetOk();
}


void LogicUnit::increase_hp(int32_t dt)																			///fixme 3초마다 meta_define::StatType_e::HPRegen를 증가시킨다. 마일스톤 2.7용. 이 후에 패시브 스킬로 대체해야 한다.
{
	m_increase_hp_time += dt;
	if (m_increase_hp_time > 3000)
	{
		int32_t current_hp = currentHp();
		int32_t max_hp = getStat(meta_define::StatType_e::Hp);
		if (current_hp < max_hp)
		{
			int32_t delta = max_hp - current_hp;
			int32_t hp_regen = getStat(meta_define::StatType_e::HPRegen);
			addCurrentHp(std::min(delta, hp_regen));
			auto logic_area = m_logic_area.lock();
			if (nullptr == logic_area)
			{
				m_increase_hp_time = 0;
				return;
			}
			logic_area->addUnitInfoMesg(shared_from_this());
		}
		m_increase_hp_time = 0;
	}
}