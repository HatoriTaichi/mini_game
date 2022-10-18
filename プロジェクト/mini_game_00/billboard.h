#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "object.h"
#include "texture.h"

class CBillboard : public CObject
{
public:
	CBillboard(LAYER_TYPE layer = LAYER_TYPE::LAYER_00);
	~CBillboard();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void BindTexture(const string &texType);			//画像の設定
	void Setpos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//頂点情報設定
	void SetColor(D3DXCOLOR col);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const string &texType, const D3DXCOLOR& col = {1.0,1.0,1.0,1.0});
	D3DXVECTOR3 GetPos() { return m_pos; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									//ワールドマトリックス	
	D3DXMATRIX m_mtxView;									//ビューマトリックス
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;										//ポリゴンサイズ
	D3DXCOLOR m_col;

};


#endif // !_BILLBOARD_H_

