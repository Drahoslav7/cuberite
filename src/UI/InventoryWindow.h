
// InventoryWindow.h

// Representing the UI window for the player inventory





#pragma once

#include "Window.h"





class cInventoryWindow :
	public cWindow
{
	typedef cWindow super;

public:
	cInventoryWindow(cPlayer & a_Player) :
		cWindow(wtInventory, "Inventory"),
		m_Player(a_Player)
	{
		m_SlotAreas.push_back(new cSlotAreaCrafting(2, *this));  // The creative inventory doesn't display it, but it's still counted into slot numbers
		m_SlotAreas.push_back(new cSlotAreaArmor(*this));
		m_SlotAreas.push_back(new cSlotAreaInventory(*this));
		m_SlotAreas.push_back(new cSlotAreaHotBar(*this));
	}


	virtual void DistributeStack(cItem & a_ItemStack, int a_Slot, cPlayer & a_Player, cSlotArea * a_ClickedArea, bool a_ShouldApply) override
	{
		cSlotAreas AreasInOrder;

		if (a_ClickedArea == m_SlotAreas[0])
		{
			// Crafting Area
			if (a_Slot == 0)
			{
				// Result Slot
				AreasInOrder.push_back(m_SlotAreas[3]);  /* Hotbar    */
				AreasInOrder.push_back(m_SlotAreas[2]);  /* Inventory */
			}
			else
			{
				AreasInOrder.push_back(m_SlotAreas[2]);  /* Inventory */
				AreasInOrder.push_back(m_SlotAreas[3]);  /* Hotbar    */
			}
			super::DistributeStack(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, (a_Slot == 0));
		}
		else if (a_ClickedArea == m_SlotAreas[1])
		{
			// Armor Area
			AreasInOrder.push_back(m_SlotAreas[2]);  /* Inventory */
			AreasInOrder.push_back(m_SlotAreas[3]);  /* Hotbar    */
			super::DistributeStack(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, false);
		}
		else if (a_ClickedArea == m_SlotAreas[2])
		{
			// Inventory Area
			AreasInOrder.push_back(m_SlotAreas[1]);  /* Armor  */
			AreasInOrder.push_back(m_SlotAreas[3]);  /* Hotbar */
			super::DistributeStack(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, false);
		}
		else
		{
			// Hotbar
			AreasInOrder.push_back(m_SlotAreas[1]);  /* Armor     */
			AreasInOrder.push_back(m_SlotAreas[2]);  /* Inventory */
			super::DistributeStack(a_ItemStack, a_Player, AreasInOrder, a_ShouldApply, false);
		}
	}
	
protected:
	cPlayer & m_Player;
};




