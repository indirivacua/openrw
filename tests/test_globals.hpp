#ifndef _TESTGLOBABLS_HPP_
#define _TESTGLOBABLS_HPP_

#include <SFML/Window.hpp>
#include <engine/GameWorld.hpp>
#include <glm/gtx/string_cast.hpp>

#define ENV_GAME_PATH_NAME ("OPENRW_GAME_PATH")

std::ostream& operator<<( std::ostream& stream, glm::vec3 const& v );

namespace boost { namespace test_tools {
template<>
struct print_log_value<glm::vec3> {
	void operator()( std::ostream& s , glm::vec3 const& v )
	{
		s << glm::to_string(v);
	}
};
}}

namespace boost { namespace test_tools {
template<>
struct print_log_value<nullptr_t> {
	void operator()( std::ostream& s , nullptr_t )
	{
		s << "nullptr";
	}
};
}}

class Global
{
public:
	sf::Window wnd;
	GameWorld* e;
	
	Global() {
		wnd.create(sf::VideoMode(640, 360), "Testing");
		glewExperimental = GL_TRUE;
		glewInit();
		e = new GameWorld(getGamePath());

		e->gameData.loadIMG("/models/gta3");
		e->gameData.loadIMG("/anim/cuts");
		e->load();
		for(std::map<std::string, std::string>::iterator it = e->gameData.ideLocations.begin();
			it != e->gameData.ideLocations.end();
			++it) {
			e->defineItems(it->second);
		}

		e->dynamicsWorld->setGravity(btVector3(0.f, 0.f, 0.f));

		while( ! e->_work->isEmpty() ) {
			std::this_thread::yield();
		}
	}

	~Global() {
		wnd.close();
		delete e;
	}

	static std::string getGamePath()
	{
		// TODO: Is this "the way to do it" on windows.
		auto v = getenv(ENV_GAME_PATH_NAME);
		return v ? v : "";
	}
	
	static Global& get()
	{
		static Global g;
		return g;
	}
};

#endif 
