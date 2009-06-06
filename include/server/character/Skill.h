/*
	------------------------------------------------------------------------------------
	LICENSE:
	------------------------------------------------------------------------------------
	This file is part of EVEmu: EVE Online Server Emulator
	Copyright 2006 - 2008 The EVEmu Team
	For the latest information visit http://evemu.mmoforge.org
	------------------------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU Lesser General Public License as published by the Free Software
	Foundation; either version 2 of the License, or (at your option) any later
	version.

	This program is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place - Suite 330, Boston, MA 02111-1307, USA, or go to
	http://www.gnu.org/copyleft/lesser.txt.
	------------------------------------------------------------------------------------
	Author:		Bloody.Rabbit
*/

#ifndef __SKILL__H__INCL__
#define __SKILL__H__INCL__

#include "inventory/InventoryItem.h"

/**
 * \class Skill
 *
 * @brief InventoryItem for skill.
 *
 * Skill class where all skill stuff is placed.
 *
 * @author Bloody.Rabbit
 * @date June 2009
 */
class Skill
: public InventoryItem
{
	friend class InventoryItem;
public:
	/**
	 * Loads skill.
	 *
	 * @param[in] factory
	 * @param[in] skillID ID of skill to load.
	 * @param[in] recurse Whether all contained items should be loaded.
	 * @return Pointer to new Skill object; NULL if fails.
	 */
	static Skill *Load(ItemFactory &factory, uint32 skillID, bool recurse=false);
	/**
	 * Spawns new skill.
	 *
	 * @param[in] factory
	 * @param[in] data Item data of new skill.
	 * @return Pointer to new Skill object; NULL if fails.
	 */
	static Skill *Spawn(ItemFactory &factory, ItemData &data);

	/*
	 * Primary public interface:
	 */
	Skill *IncRef() { return static_cast<Skill *>( InventoryItem::IncRef() ); }

	/**
	 * Calculates required amount of skillpoints for level.
	 *
	 * @param[in] level Level to calculate SP for.
	 * @return Amount of SP required.
	 */
	uint32 GetSPForLevel(uint8 level);
	/**
	 * Checks whether requirements of skill has been fulfilled.
	 *
	 * @param[in] ch Character which is checked.
	 * @return True if requirements are OK, false if not.
	 */
	bool SkillPrereqsComplete(Character &ch);

protected:
	Skill(
		ItemFactory &_factory,
		uint32 _skillID,
		// InventoryItem stuff:
		const Type &_type,
		const ItemData &_data );

	/*
	 * Member functions
	 */
	// Template loader:
	template<class _Ty>
	static _Ty *_LoadItem(ItemFactory &factory, uint32 skillID,
		// InventoryItem stuff:
		const Type &type, const ItemData &data)
	{
		// check it's a skill
		if( type.categoryID() != EVEDB::invCategories::Skill )
		{
			_log( ITEM__ERROR, "Trying to load %s as Skill.", type.category().name().c_str() );
			return NULL;
		}

		// no additional stuff

		return _Ty::_LoadSkill( factory, skillID, type, data );
	}

	// Actual loading stuff:
	static Skill *_Load(ItemFactory &factory, uint32 skillID
	);
	static Skill *_LoadItem(ItemFactory &factory, uint32 skillID,
		// InventoryItem stuff:
		const Type &type, const ItemData &data
	);
	static Skill *_LoadSkill(ItemFactory &factory, uint32 skillID,
		// InventoryItem stuff:
		const Type &type, const ItemData &data
	);

	bool _Load(bool recurse=false) { return InventoryItem::_Load(recurse); }

	static uint32 _Spawn(ItemFactory &factory,
		// InventoryItem stuff:
		ItemData &data
	);
};

#endif /* !__SKILL__H__INCL__ */
