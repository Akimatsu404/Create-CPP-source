#ifndef __UI_H_
#define __UI_H_

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "../png/png.h"
#include "../base.h"

namespace AKIMATSU_LIB {

enum UI_TYPE {
	NONE,
	COUNTER,
};

namespace UI_SETTING {

struct UI_SETTING_PRESET {
	UI_TYPE type;
	std::string name;
	glm::vec3 position;
	const char* filename;
};

class UI_SETTING {
	UI_TYPE m_type;
	std::string m_name;
	glm::vec3 m_position;
	//	std::map<std::string, std::unique_ptr<TEXTURE>> texMap;
	std::shared_ptr<TEXTURE> m_texture;

	void CounterUpdate();
	void CounterRender();

public:
	UI_SETTING(UI_SETTING_PRESET v_preset);
	~UI_SETTING();

	void Update();
	void Render();

	UI_TYPE GetType();

};
}


namespace UI_CONTROL {

	struct OUTER_DATA {



	};

class UI_CONTROL {

	//UIの中心位置
	glm::vec3 m_position;
	std::vector<UI_SETTING::UI_SETTING> m_settingArray;

public:
	UI_CONTROL(glm::vec3 v_position);
	~UI_CONTROL();

	void Add(UI_SETTING::UI_SETTING v_setting, const char* filename);
	void Update();
	void Render();

	//外部から必要なデータを受け入れる関数
	void SetData();

};
}
}



#endif