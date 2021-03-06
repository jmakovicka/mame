// license:LGPL-2.1+
// copyright-holders:Tomasz Slanina
#include "emu.h"
#include "includes/ssrj.h"

/* tilemap 1 */

WRITE8_MEMBER(ssrj_state::vram1_w)
{
	m_vram1[offset] = data;
	m_tilemap1->mark_tile_dirty(offset>>1);
}

TILE_GET_INFO_MEMBER(ssrj_state::get_tile_info1)
{
	int code;
	code = m_vram1[tile_index<<1] + (m_vram1[(tile_index<<1)+1]<<8);
	SET_TILE_INFO_MEMBER(0,
		code&0x3ff,
		(code>>12)&0x3,
		((code & 0x8000) ? TILE_FLIPY:0) |( (code & 0x4000) ? TILE_FLIPX:0) );
}

/* tilemap 2 */

WRITE8_MEMBER(ssrj_state::vram2_w)
{
	m_vram2[offset] = data;
	m_tilemap2->mark_tile_dirty(offset>>1);
}

TILE_GET_INFO_MEMBER(ssrj_state::get_tile_info2)
{
	int code;
	code = m_vram2[tile_index<<1] + (m_vram2[(tile_index<<1)+1]<<8);
	SET_TILE_INFO_MEMBER(0,
		code&0x3ff,
		((code>>12)&0x3)+4,
		((code & 0x8000) ? TILE_FLIPY:0) |( (code & 0x4000) ? TILE_FLIPX:0) );
}

/* tilemap 4 */

WRITE8_MEMBER(ssrj_state::vram4_w)
{
	m_vram4[offset] = data;
	m_tilemap4->mark_tile_dirty(offset>>1);
}

TILE_GET_INFO_MEMBER(ssrj_state::get_tile_info4)
{
	int code;
	code = m_vram4[tile_index<<1] + (m_vram4[(tile_index<<1)+1]<<8);
	SET_TILE_INFO_MEMBER(0,
		code&0x3ff,
		((code>>12)&0x3)+12,
		((code & 0x8000) ? TILE_FLIPY:0) |( (code & 0x4000) ? TILE_FLIPX:0) );
}


/*
TODO: This table is nowhere near as accurate. If you bother, here's how colors should be:
-"START" sign is red with dark blue background.
-Sidewalk is yellow-ish.
-first opponents have swapped colors (blue/yellow instead of yellow/blue)
-after the first stage, houses have red/white colors.
*/

static const UINT8 fakecols[4*4][8][3]=
{
{{0x00,0x00,0x00},
	{42,87,140},
	{0,0,0},
	{33,75,160},
	{0xff,0xff,0xff},
	{37,56,81},
	{0x1f,0x1f,0x2f},
	{55,123,190}},

{{0x00,0x00,0x00},
	{0x00,99,41},
	{0x00,0x00,0xff},
	{0x00,0xff,0},
	{255,255,255},
	{0xff,0x00,0x00},
	{0,45,105},
	{0xff,0xff,0}},


{{0x00,0x00,0x00},
	{0x00,0x20,0x00},
	{0x00,0x40,0x00},
	{0x00,0x60,0x00},
	{0x00,0x80,0x00},
	{0x00,0xa0,0x00},
	{0x00,0xc0,0x00},
	{0x00,0xf0,0x00}},

	{{0x00,0x00,0x00},
	{0x20,0x00,0x20},
	{0x40,0x00,0x40},
	{0x60,0x00,0x60},
	{0x80,0x00,0x80},
	{0xa0,0x00,0xa0},
	{0xc0,0x00,0xc0},
	{0xf0,0x00,0xf0}},

{{0x00,0x00,0x00},
	{0xff,0x00,0x00},
	{0x7f,0x00,0x00},
	{0x00,0x00,0x00},
	{0x00,0x00,0x00},
	{0xaf,0x00,0x00},
	{0xff,0xff,0xff},
	{0xff,0x7f,0x7f}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{{0x00,0x00,0x00},
	{0xff,0x00,0x00},
	{0x00,0x00,0x9f},
	{0x60,0x60,0x60},
	{0x00,0x00,0x00},
	{0xff,0xff,0x00},
	{0x00,0xff,0x00},
	{0xff,0xff,0xff}},

{
	{0x00,0x00,0x00},
	{0x00,0x00,0xff},
	{0x00,0x00,0x7f},
	{0x00,0x00,0x00},
	{0x00,0x00,0x00},
	{0x00,0x00,0xaf},
	{0xff,0xff,0xff},
	{0x7f,0x7f,0xff}},

{{0x00,0x00,0x00},
	{0xff,0xff,0x00},
	{0x7f,0x7f,0x00},
	{0x00,0x00,0x00},
	{0x00,0x00,0x00},
	{0xaf,0xaf,0x00},
	{0xff,0xff,0xff},
	{0xff,0xff,0x7f}},

{{0x00,0x00,0x00},
	{0x00,0xff,0x00},
	{0x00,0x7f,0x00},
	{0x00,0x00,0x00},
	{0x00,0x00,0x00},
	{0x00,0xaf,0x00},
	{0xff,0xff,0xff},
	{0x7f,0xff,0x7f}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{{0x00,0x00,0x00},
	{0x20,0x20,0x20},
	{0x40,0x40,0x40},
	{0x60,0x60,0x60},
	{0x80,0x80,0x80},
	{0xa0,0xa0,0xa0},
	{0xc0,0xc0,0xc0},
	{0xf0,0xf0,0xf0}},

{
	{0x00,0x00,0x00},
	{0xff,0xaf,0xaf},
	{0x00,0x00,0xff},
	{0xff,0xff,0xff},
	{0x00,0x00,0x00},
	{0xff,0x50,0x50},
	{0xff,0xff,0x00},
	{0x00,0xff,0x00}
}

};

void ssrj_state::video_start()
{
	m_tilemap1 = &machine().tilemap().create(m_gfxdecode, tilemap_get_info_delegate(FUNC(ssrj_state::get_tile_info1),this), TILEMAP_SCAN_COLS, 8, 8, 32, 32);
	m_tilemap2 = &machine().tilemap().create(m_gfxdecode, tilemap_get_info_delegate(FUNC(ssrj_state::get_tile_info2),this), TILEMAP_SCAN_COLS, 8, 8, 32, 32);
	m_tilemap4 = &machine().tilemap().create(m_gfxdecode, tilemap_get_info_delegate(FUNC(ssrj_state::get_tile_info4),this), TILEMAP_SCAN_COLS, 8, 8, 32, 32);
	m_tilemap2->set_transparent_pen(0);
	m_tilemap4->set_transparent_pen(0);

	m_buffer_spriteram = std::make_unique<UINT8[]>(0x0800);
}


void ssrj_state::draw_objects(bitmap_ind16 &bitmap, const rectangle &cliprect )
{
	int i,j,k,x,y;

	for(i=0;i<6;i++)
	{
		y = m_buffer_spriteram[0x80+20*i];
		x = m_buffer_spriteram[0x80+20*i+2];
		if (!m_buffer_spriteram[0x80+20*i+3])
		{
			for(k=0;k<5;k++,x+=8)
			{
				for(j=0;j<0x20;j++)
				{
					int code;
					int offs = (i * 5 + k) * 64 + (31 - j) * 2;

					code = m_vram3[offs] + 256 * m_vram3[offs + 1];
					m_gfxdecode->gfx(0)->transpen(bitmap,
						cliprect,
						code&1023,
						((code>>12)&0x3)+8,
						code&0x4000,
						code&0x8000,
						x,
						(247-(y+(j<<3)))&0xff,
						0);
				}
			}
		}
	}
}


PALETTE_INIT_MEMBER(ssrj_state, ssrj)
{
	int i, j;
	for(i=0; i<4*4; i++)
		for(j=0; j<8; j++)
			palette.set_pen_color(i*8+j, fakecols[i][j][0], fakecols[i][j][1], fakecols[i][j][2]);
}

UINT32 ssrj_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	m_tilemap1->set_scrollx(0, 0xff-m_scrollram[2] );
	m_tilemap1->set_scrolly(0, m_scrollram[0] );
	m_tilemap1->draw(screen, bitmap, cliprect, 0, 0);
	draw_objects(bitmap, cliprect);
	m_tilemap2->draw(screen, bitmap, cliprect, 0, 0);

	if (m_scrollram[0x101] == 0xb) m_tilemap4->draw(screen, bitmap, cliprect, 0, 0);/* hack to display 4th tilemap */
	return 0;
}

void ssrj_state::screen_eof(screen_device &screen, bool state)
{
	// rising edge
	if (state)
	{
		memcpy(m_buffer_spriteram.get(), m_scrollram, 0x800);
	}
}
