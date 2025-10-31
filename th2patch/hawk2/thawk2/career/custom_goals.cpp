#include "stdafx.h"
#include "custom_goals.h"

namespace CustomGoals
{
	SGoal FoundryGoals[10] = {
		// goalType, intParam, stringParam, cashAward, goalText, unk

		// foundry
		{ EGoalType::Score,		10000,	NULL,		1000, "High Score - 10,000", 0 },
		{ EGoalType::Score,		25000,	NULL,		1000, "Pro Score - 25,000", 0 },
		{ EGoalType::Score,		75000,	NULL,		1000, "Sick Score - 75,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Destroy,	5,		"valves",	1000, "Valves Unjammed", 0 },
		{ EGoalType::Pickups,	0,		NULL,		1000, "!BROKEN! Activate Press", 0 },
		{ EGoalType::Trick,		0,		"INDY",		1000, "Indy over the halfpipe", 0},
		{ EGoalType::Gaps,		1,		NULL,		1000, "Grind the control booth", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};

	SGoal CanadaGoals[10] = {
		{ EGoalType::Score,		15000,	NULL,		1000, "High score - 15,000", 0 },
		{ EGoalType::Score,		40000,	NULL,		1000, "Pro score - 40,000", 0 },
		{ EGoalType::Score,		100000,	NULL,		1000, "Sick score - 100,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Destroy,	5,		"poles",	1000, "Totem poles", 0 },
		{ EGoalType::Pickups,	0,		NULL,		1000, "!BROKEN! Blow up the tree", 0 },
		{ EGoalType::Trick,		0,		"NOSEGRIND",1000, "Nosegrind over the tree", 0 },
		{ EGoalType::Gaps,		1,		NULL,		1000, "Jump over the pool", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};

	SGoal AirportGoals[10] = {
		{ EGoalType::Score,		20000,	NULL,		1000, "High score - 20,000", 0 },
		{ EGoalType::Score,		50000,	NULL,		1000, "Pro score - 50,000", 0 },
		{ EGoalType::Score,		150000,	NULL,		1000, "Sick score - 150,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Pickups,	5,		"flags",	1000, "!BROKEN! Snag the flags", 0 },
		{ EGoalType::Destroy,	5,		"suitcases",1000, "Lost luggage found!", 0},
		{ EGoalType::Trick,		0,		"NOSEBLUNTSLIDE",1000, "Nosebluntslide the airport sign", 0 },
		{ EGoalType::Gaps,		1,		NULL,		1000, "Grind the plane", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};

	SGoal SuburbiaGoals[10] = {
		{ EGoalType::Score,		40000,	NULL,		1000, "High score - 20,000", 0 },
		{ EGoalType::Score,		100000,	NULL,		1000, "Pro score - 100,000", 0 },
		{ EGoalType::Score,		200000,	NULL,		1000, "Sick score - 200,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Destroy,	5,		"appliances",1000, "Appall the appliances", 0 },
		{ EGoalType::Pickups,	5,		"dishes",	1000, "!BROKEN! Disrespect the dishes", 0},
		{ EGoalType::Gaps,		1,		NULL,		1000, "Ice the ice cream man", 0 },
		{ EGoalType::Trick,		1,		"360 FLIP",	1000, "360 flip the weathervane", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};

	SGoal LosAngelesGoals[10] = {
		{ EGoalType::Score,		50000,	NULL,		1000, "High score - 50,000", 0 },
		{ EGoalType::Score,		125000,	NULL,		1000, "Pro score - 125,000", 0 },
		{ EGoalType::Score,		250000,	NULL,		1000, "Sick score - 250,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Destroy,	5,		"transformers",	1000, "Transformers shutdown", 0 },
		{ EGoalType::Pickups,	1,		NULL,		1000, "Grind the electric rail", 0},
		{ EGoalType::Gaps,		1,		NULL,		1000, "Elevator grind", 0 },
		{ EGoalType::Trick,		1,		"KICKFLIP",	1000, "Kickflip over elevator lobby", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};

	void PatchThps3Goals(void * pLevels)
	{
		SLevel* pLevel = (SLevel*)pLevels;

		memcpy(pLevel->Goals, FoundryGoals, sizeof(SGoal) * 10); pLevel++;
		memcpy(pLevel->Goals, CanadaGoals, sizeof(SGoal) * 10); pLevel++;
		pLevel++;
		memcpy(pLevel->Goals, AirportGoals, sizeof(SGoal) * 10); pLevel++;
		memcpy(pLevel->Goals, SuburbiaGoals, sizeof(SGoal) * 10); pLevel++;
		pLevel++;
		memcpy(pLevel->Goals, LosAngelesGoals, sizeof(SGoal) * 10);
		/*
		sprintf(level->name, "Foundry");
		level->subname = "Woodland Hills";
		level->shortname = "foun";
		level->trgfile = "aafoun_t";

		level->gapFirst = 2500; // +
		level->gapLast = 2600;

		level++;

		sprintf(level->name, "Canada");
		level->subname = "Alberta";
		level->shortname = "can";
		level->trgfile = "aacan_t";

		level->gapFirst = 2000; // +
		level->gapLast = 2100;

		level++;

		sprintf(level->name, "Rio de Janeiro");
		level->subname = "Brazil";
		level->shortname = "rio";
		level->trgfile = "aario_t";

		level->gapFirst = 2400; // +
		level->gapLast = 2500;

		level++;

		sprintf(level->name, "Airport");
		level->subname = "Hawaii?";
		level->shortname = "air";
		level->trgfile = "aaair_t";

		level->gapFirst = 2300; // +
		level->gapLast = 2400;

		level++;

		sprintf(level->name, "Suburbia");
		level->subname = "USA";
		level->shortname = "sub";
		level->trgfile = "aaburb_t";

		level->gapFirst = 2100; // +
		level->gapLast = 2200;

		level++;

		sprintf(level->name, "Skater Island");
		level->subname = "Middletown";
		level->shortname = "si";
		level->trgfile = "aaskil_t";

		level->gapFirst = 2200; // +
		level->gapLast = 2300;

		level++;

		sprintf(level->name, "Los Angeles");
		level->subname = "California";
		level->shortname = "LA";
		level->trgfile = "aala_t";

		level->gapFirst = 1000; // +
		level->gapLast = 1100;

		level++;

		sprintf(level->name, "Tokyo");
		level->subname = "Japan";
		level->shortname = "tok";
		level->trgfile = "aajap_t";

		level->gapFirst = 2600; // +
		level->gapLast = 2700;

		level++;

		sprintf(level->name, "Dowhhill");
		level->subname = "Brazil";
		level->shortname = "dnhl";
		level->trgfile = "aadnhl_t";

		level->gapFirst = 2800; // +
		level->gapLast = 2900;

		*/
	}


	SGoal WarehouseGoals[10] = {
		// goalType, intParam, stringParam, cashAward, goalText, unk

		// foundry
		{ EGoalType::Score,		10000,	NULL,		1000, "High Score - 10,000", 0 },
		{ EGoalType::Score,		25000,	NULL,		1000, "Pro Score - 25,000", 0 },
		{ EGoalType::Score,		75000,	NULL,		1000, "Sick Score - 75,000", 0 },
		{ EGoalType::Skate,		0,		NULL,		1000, "Collect S-K-A-T-E", 0 },
		{ EGoalType::Destroy,	5,		"boxes",	1000, "Smash the boxes", 0 },
		{ EGoalType::Pickups,	0,		NULL,		1000, "--- non-working slot ---", 0 },
		{ EGoalType::Trick,		1,		"NOSEGRIND",	1000, "50-50 the Big Rail Gap", 0},
		{ EGoalType::Gaps,		1,		NULL,		1000, "Ollie a Channel gap", 0 },

		{ EGoalType::Hidden,	0,		NULL,		1000, "Find the secret tape", 0 },
		{ EGoalType::Clear,		0,		NULL,		1000, "100% goals, stats and decks", 0 }
	};


	void PatchThps1Goals(void* pLevels)
	{
		SLevel* pLevel = (SLevel*)pLevels;

		pLevel->gapFirst = 0;
		pLevel->gapLast = 0;

		memcpy(pLevel->Goals, WarehouseGoals, sizeof(SGoal) * 10); pLevel++;


		/*
		level = (SLevel*)((int)Levels + sizeof(SLevel) * 1);

		level->trgfile = "skschl_t";
		level->shortname = "schl";
		level->subname = "School Miami";
		level->gapStart = 0;
		level->gapEnd = 25000;

		goal = GetGoal(1, 4);
		goal->goalText = "Grind 5 picnic tables";
		goal->stringParam = "picnic tables";

		goal = GetGoal(1, 6);
		goal->intParam = 1;
		goal->goalText = "Nosegrind the handicap";
		goal->stringParam = "NOSEGRIND";

		goal = GetGoal(1, 7);
		goal->intParam = 2;
		goal->goalText = "Hit 2 playground transfers";
		goal->stringParam = "TRANSFERS";


		SLevel* level = Levels + 0;

		level->trgfile = "skware_t";
		level->shortname = "ware";
		sprintf(level->name, "%s", "Warehouse");
		level->subname = "Woodland Hills";
		level->gapFirst = 11000;
		level->gapLast = 11002;

		*/

	}

	void PatchThps4Goals(void* pLevels)
	{
		throw exception("Not implemented!");
	}

	void PatchCareerGoals(void* pLevels)
	{
		if (options.CurrentGame == "THPS1")
			return PatchThps1Goals(pLevels);

		if (options.CurrentGame == "THPS3")
			return PatchThps3Goals(pLevels);
	}
}