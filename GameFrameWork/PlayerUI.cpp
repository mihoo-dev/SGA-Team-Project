#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"


PlayerUI::PlayerUI()
	:_isInven(false), _isOnceClicked(false)
{
}


PlayerUI::~PlayerUI()
{
}

HRESULT PlayerUI::init()
{
	IMAGEMANAGER->addImage("HPBack", "PlayerHPUIBack.bmp", 144, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPFront", "PlayerHPUIFront.bmp", 40, 46, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("SwordUI", "PlayerSwordUI.bmp", 70, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Inventory", "Inventory.bmp", 600, 500, false, NULL);
	IMAGEMANAGER->addFrameImage("InventoryItem", "InventoryItem.bmp", 174, 66, 3, 1, true, RGB(255, 0, 255));

	if(TXTDATA->txtLoad("ItemInfo.txt").size() > 0)
		_loadInven = TXTDATA->txtLoad("ItemInfo.txt");

	for (int i = 0; i < _loadInven.size(); i++)
	{
		_vInven.push_back(atoi(_loadInven[i].c_str()));
	}
	/*int num = 0;
	for (int i = 0; i < 8; i++)
	{
	for (int j = 0; j < 5; j++)
	{
	_vInven.push_back(num++);
	if (num >= 2) num = 0;
	}
	}*/

	return S_OK;
}

void PlayerUI::release()
{
	_loadInven.clear();
	_vInven.clear();
}

void PlayerUI::update()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_isInven)
			InitInvenPos();
	}

	if (KEYMANAGER->isToggleKey('I'))
		_isInven = true;
	else _isInven = false;

	if (_isInven)
		UpdateInven();
}

void PlayerUI::render()
{
	IMAGEMANAGER->findImage("HPBack")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());
	for (int i = 0; i < _playerHP; i++)
		IMAGEMANAGER->findImage("HPFront")->render(getMemDC(), CAMERA->GetX() + (i * 40), CAMERA->GetY());
	if (_weapon)
		IMAGEMANAGER->findImage("SwordUI")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY() + 50);

	if (_isInven)
	{
		IMAGEMANAGER->findImage("Inventory")->render(getMemDC(), CAMERA->GetX(), CAMERA->GetY());

		DrawInventory();

        HFONT hFont = CreateFont(30, 30, 0, 0, 50, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
        HFONT hOFont = (HFONT)SelectObject(getMemDC(), hFont);
        SetTextColor(getMemDC(), RGB(255, 255, 0));
        TextOut(getMemDC(), CAMERA->GetX() + 30, CAMERA->GetRC().bottom - 50, to_string(_coin).c_str(), to_string(_coin).size());
        SelectObject(getMemDC(), hOFont);
        DeleteObject(hFont);
    }
}

void PlayerUI::SetPlayerInfo(Player * player)
{
    _playerInfo = player;

	_playerHP = player->GetInfo().hp;
	_weapon = player->GetInfo().weapon;
    _coin = player->GetInfo().coin;
    _star = player->GetInfo().star;
}

void PlayerUI::SetInventoryVector(int type)
{

}

void PlayerUI::InitInvenPos()
{
	int num = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (num < _vInven.size())
			{
				_inventory[j][i] = Inven(24 + (j * 2) + CAMERA->GetX() + j * 58,
					79 + (i * 1) + CAMERA->GetY() + i * 66, _vInven[num++]);
			}
			else
				_inventory[j][i] = Inven(24 + (j * 2) + CAMERA->GetX() + j * 58,
					79 + (i * 1) + CAMERA->GetY() + i * 66, (int)Inven::DEFFAULT);

		}
	}
}

void PlayerUI::DrawInventory()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_inventory[i][j].type == (int)Inven::DEFFAULT) continue;

			//Rectangle(getMemDC(), _inventory[i][j].rc.left, _inventory[i][j].rc.top, _inventory[i][j].rc.right, _inventory[i][j].rc.bottom);
			IMAGEMANAGER->findImage("InventoryItem")->frameRender(getMemDC(),
				_inventory[i][j].x,
				_inventory[i][j].y, _inventory[i][j].type, 0);
		}
	}
}

void PlayerUI::UpdateInven()
{
	if (!_isOnceClicked)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (CAMERA->GetX() + _ptMouse.x > _inventory[i][j].rc.left &&
						CAMERA->GetX() + _ptMouse.x < _inventory[i][j].rc.right &&
						CAMERA->GetY() + _ptMouse.y > _inventory[i][j].rc.top &&
						CAMERA->GetY() + _ptMouse.y < _inventory[i][j].rc.bottom)
					{
						if (_inventory[i][j].type == (int)Inven::DEFFAULT) continue;

						_inventory[i][j].isOnceClicked = true;
						_isOnceClicked = true;
					}
				}
			}
		}
	}
	else if (_isOnceClicked)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (CAMERA->GetX() + _ptMouse.x > _inventory[i][j].rc.left &&
						CAMERA->GetX() + _ptMouse.x < _inventory[i][j].rc.right &&
						CAMERA->GetY() + _ptMouse.y > _inventory[i][j].rc.top &&
						CAMERA->GetY() + _ptMouse.y < _inventory[i][j].rc.bottom)
					{
						if (_inventory[i][j].isOnceClicked)
						{
                            if (_inventory[i][j].type == (int)Inven::POTION)
                                _playerInfo->SetHP(++_playerHP);
                            else if (_inventory[i][j].type == (int)Inven::STAR)
                                _playerInfo->SetStar(++_star);

							_vInven.erase(_vInven.begin() + (i + (j * 8)));
							_loadInven.erase(_loadInven.begin() + (i + (j * 8)));
							_inventory[i][j].type = (int)Inven::DEFFAULT;
							_inventory[i][j].isOnceClicked = false;
							_isOnceClicked = false;
							InitInvenPos();
							
							TXTDATA->txtSave("ItemInfo.txt", _loadInven);
						}
					}
					else
					{
						if (_inventory[i][j].isOnceClicked)
						{
							_inventory[i][j].isOnceClicked = false;
							_isOnceClicked = false;
						}
					}
				}
			}
		}
	}
}
