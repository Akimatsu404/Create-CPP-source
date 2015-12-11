#include "UI.h"

namespace AKIMATSU_LIB {

namespace UI_SETTING {
UI_SETTING::UI_SETTING(UI_SETTING_PRESET v_preset) {

	m_type = v_preset.type;
	m_name = v_preset.name;
	m_position = v_preset.position;
	std::shared_ptr<TEXTURE> t_tex(new TEXTURE(v_preset.filename));
	m_texture = std::move(t_tex);

}

UI_SETTING::~UI_SETTING() {}

void UI_SETTING::Update() {

	if (m_type == UI_TYPE::COUNTER) {
		//�O�����琔�l�f�[�^���󂯓���āA�X�V����


	}

}

void UI_SETTING::Render() {

	if (m_type == UI_TYPE::COUNTER) {
		//�O�����琔�l�f�[�^���󂯓���āA�`�悷��B

	}

}



UI_TYPE UI_SETTING::GetType() {
	return m_type;
}


}



//////////////// UI����
namespace UI_CONTROL {
UI_CONTROL::UI_CONTROL(glm::vec3 v_position) : m_position(v_position) {
}


void UI_CONTROL::Add(UI_SETTING::UI_SETTING v_setting, const char* filename) {


	m_settingArray.push_back(v_setting);

}

void UI_CONTROL::Update() {

	for (int i = 0; i < m_settingArray.size(); ++i) {
		m_settingArray[i].Update();
	}

}

void UI_CONTROL::Render() {

	for (int i = 0; i < m_settingArray.size(); ++i) {
		m_settingArray[i].Render();
	}

}
}

}