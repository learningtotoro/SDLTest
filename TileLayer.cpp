#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : m_tileSize(tileSize),
	m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize);
	m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update()
{
	m_position += m_velocity;
	m_velocity.setX(1);
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;
	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;
	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	// 这里的numRows和numColumns不是整张Texture的大小，而是所需的尺寸
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j + x];

			// 空白块，不用绘制
			if (id == 0)
			{
				continue;
			}
			Tileset tileset = getTilesetByID(id);
			id--;
			TheTextureManager::Instance()->drawTile(tileset.name, 2, 2,
				(j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize,
				m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, 
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::Instance()->getRenderer());
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}

	// 返回空 tileset
	std::cout << "did not find tileset, returning empy tileset" << std::endl;
	Tileset t;
	return t;
}