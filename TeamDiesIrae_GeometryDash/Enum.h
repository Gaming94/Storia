#pragma once

namespace ObjID
{
	enum ID
	{
		//SCENE
		OBJ_LOADING = 0,
		OBJ_BG_EFFECT,
		OBJ_SELECTCHARACTER,
		OBJ_SELECTMODE,
		OBJ_TUTORIAL,
		OBJ_SELECTSTAGE,
		OBJ_ROCOTOWN,
		OBJ_VOLACONO,
		OBJ_BEROIA,
		OBJ_SANCTUARY,
		OBJ_RAVEN,
		OBJ_MINIGAME,

		//AttackRect
		OBJ_ATTACKRECT,

		//Shadow
		OBJ_SHADOW,

		//NPC
		OBJ_NPC,

		//OBJECT
		OBJ_CHARACTER,
		OBJ_UI,

		//미니게임용
		OBJ_CHARACTER2,
		OBJ_CHARACTER3,
		OBJ_NUMBERING,

		//MONSTER
		OBJ_MONSTER,

		//EFFECT
		OBJ_EFFECT,

		//기타 오브젝트
		OBJ_BLENDOBJ,
		OBJ_CHARILLUST,
		OBJ_TEXTBOX,
		OBJ_TEXT,
		OBJ_SKILLBOX,

		//BackGroundAlphaEffect
		OBJ_ALPHAEFFECT,

		//End
		OBJ_END
	};
}

namespace Char_StanceID
{
	enum ID
	{
		IDLE_L,
		IDLE_R,

		WALK_L,
		WALK_R,

		ATTACK_L,
		ATTACK_R,
		SKILL_R,
		
		HIT_L,
		HIT_R,

		SKILL_X_L,
		SKILL_X_R,

		RUNAWAY,
		
		END
	};
}

namespace eChar_Num
{
	enum ID
	{
		ALPONSO = 1,
		LEO,

		CHAR_END
	};
}

namespace eItem_Num
{
	enum ID
	{
		ITEM_CLUB = 1,
		

		ITEM_END
	};
}