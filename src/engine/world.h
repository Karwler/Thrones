#pragma once

#include "windowSys.h"
#include "prog/program.h"

// class that makes accessing stuff easier
class World {
public:
	static inline Arguments args;
private:
	static inline WindowSys windowSys;	// the thing on top of which everything runs

public:
	static WindowSys* window();
	static AudioSys* audio();
	static FontSet* fonts();
	static Game* game();
	static InputSys* input();
	static Netcp* netcp();
	static GuiGen* pgui();
	static Program* program();
	static ProgState* state();
	template <class T> static T* state();
	static Settings* sets();
	static Scene* scene();
	static const ShaderGeometry* geom();
#ifndef OPENGLES
	static const ShaderDepth* depth();
#endif
	static const ShaderGui* sgui();

	template <class C> static void setArgs(int argc, const C* const* argv);
	template <class F, class... A> static void prun(F func, A&&... argv);
	template <class F, class... A> static void srun(F func, A&&... argv);
};

inline WindowSys* World::window() {
	return &windowSys;
}

inline AudioSys* World::audio() {
	return windowSys.getAudio();
}

inline FontSet* World::fonts() {
	return windowSys.getFonts();
}

inline Game* World::game() {
	return windowSys.getProgram()->getGame();
}

inline InputSys* World::input() {
	return windowSys.getInput();
}

inline Netcp* World::netcp() {
	return windowSys.getProgram()->getNetcp();
}

inline GuiGen* World::pgui() {
	return windowSys.getProgram()->getGui();
}

inline Program* World::program() {
	return windowSys.getProgram();
}

inline ProgState* World::state() {
	return windowSys.getProgram()->getState();
}

template <class T>
T* World::state() {
	return windowSys.getProgram()->getState<T>();
}

inline Scene* World::scene() {
	return windowSys.getScene();
}

inline Settings* World::sets() {
	return windowSys.getSets();
}

inline const ShaderGeometry* World::geom() {
	return windowSys.getGeom();
}

#ifndef OPENGLES
inline const ShaderDepth* World::depth() {
	return windowSys.getDepth();
}
#endif

inline const ShaderGui* World::sgui() {
	return windowSys.getGui();
}

template <class F, class... A>
void World::prun(F func, A&&... argv) {
	if (func)
		(program()->*func)(std::forward<A>(argv)...);
}

template <class F, class... A>
void World::srun(F func, A&&... argv) {
	if (func)
		(state()->*func)(std::forward<A>(argv)...);
}
