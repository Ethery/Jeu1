#include <SFML\Graphics.hpp>

#define PI 3.141592653589793238462

class Timer : public sf::Drawable, public sf::Transformable
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// on applique la transformation
		states.transform *= getTransform();

		// et on dessine enfin le tableau de vertex
		target.draw(m_array, states);
	}

	sf::VertexArray m_array;
	sf::Color color;

public:

	Timer(sf::Color c)
	{
		color = c;
	}

	Timer(sf::Vector2i p,int rayon, int div, int val, sf::Color couleur)
	{
		int size = 800;
		m_array = sf::VertexArray(sf::TrianglesFan, size);
		float an = ((float)size / (float)div)*(float)val;
		m_array[0].position = sf::Vector2f(p.x, p.y);
		m_array[0].color = couleur;
		for (int i = 1; i < size - 1; i++)
		{
			float angle = 2 * PI / size * i;
			if (i > an)
			{
				m_array[i].position = sf::Vector2f((sin(angle) * rayon) + p.x, (-cos(angle) * rayon) + p.y);
			}
			else
			{
				m_array[i].position = sf::Vector2f((sin(angle) * 0) + p.x, (-cos(angle) * 0) + p.y);
			}
			m_array[i].color = couleur;
		}

		m_array[size - 1].position = sf::Vector2f(p.x, p.y);
		m_array[size - 1].color = couleur;
	}

	void reload(sf::Vector2i p, int rayon, int div, int val)
	{
		int size = 800;
		m_array = sf::VertexArray(sf::TrianglesFan, size);
		float an = ((float)size / (float)div)*(float)val;
		m_array[0].position = sf::Vector2f(p.x, p.y);
		m_array[0].color = color;
		for (int i = 1; i < size - 1; i++)
		{
			float angle = 2 * PI / size * i;
			if (i > an)
			{
				m_array[i].position = sf::Vector2f((sin(angle) * rayon) + p.x, (-cos(angle) * rayon) + p.y);
			}
			else
			{
				m_array[i].position = sf::Vector2f((sin(angle) * 0) + p.x, (-cos(angle) * 0) + p.y);
			}
			m_array[i].color = color;
		}

		m_array[size - 1].position = sf::Vector2f(p.x, p.y);
		m_array[size - 1].color = color;
	}

	void setColor(sf::Color c)
	{
		color = c;
	}
};










/*

*/