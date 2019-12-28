//=====================================
//
//FontManager.h
//�@�\:�t�H���g�}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <map>
#include <vector>

/**************************************
FontResourceKey�N���X
***************************************/
class FontResourceKey
{
public:
	std::string fontName;
	int fontSize;

	FontResourceKey(std::string name, int size);

	bool operator < (const FontResourceKey& rhs) const;
};

/**************************************
�N���X��`
***************************************/
class FontManager : public BaseSingleton<FontManager>
{
	friend class BaseSingleton<FontManager>;
public:
	//�t�H���g�ǂݍ��ݏ���
	//���O�̃t�H���g���g�p����ꍇ�Ƀt�H���g���ꎞ�I�ɃC���X�g�[������
	//fontFileName : �C���X�g�[������t�H���g�t�@�C���ւ̃p�X
	void LoadFont(const char* filePath);

	//�t�H���g�A���C���X�g�[������
	//�ꎞ�I�ɃC���X�g�[���������O�̃t�H���g���A���C���X�g�[������
	//fontFileName : �A���C���X�g�[���t�H���g�t�@�C���ւ̃p�X
	void RemoveFont(const char* filePath);

	//�t�H���g���\�[�X�������
	void ClearAll();

	//�t�H���g�擾����
	LPD3DXFONT GetFont(const std::string& fontName, int fontSize);
	LPD3DXFONT GetItalicFont(const std::string& fontName, int fontSize);

private:
	void _CreateFont(const FontResourceKey& key);
	void _CreateItalicFont(const FontResourceKey& key);

	FontManager() {}
	FontManager(const FontManager&) {}

	~FontManager();
	
	std::map<FontResourceKey, LPD3DXFONT> fontPool;
	std::map<FontResourceKey, LPD3DXFONT> italicFontPool;
	std::vector<std::string> loadFontContainer;
};
#endif