#pragma once

#include "../../components/button.hpp"
#include "../../constants.hpp"
#include "../../utils/bdsp.hpp"
#include "../detachable-view.hpp"
#include "./../../utils/debug.hpp"
#include <csight-core.h>
#include <memory>
#include <string>
#include <tesla.hpp>

class CustomDaycareView : public DetachableView {
 public:
  CustomDaycareView() : DetachableView("Daycare View (Custom)") { }

  virtual void setupList(tsl::elm::List *list) {
    list->addItem(new tsl::elm::CategoryHeader("Offset"));
    m_offset_item = new tsl::elm::ListItem("");
    list->addItem(m_offset_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP"));
    m_tmp_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp_item);
  }

  virtual void handleInputIfAttached(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick,
                                     HidAnalogStickState rightJoyStick) { }

  virtual void update() {
    u64 offset = get_player_prefs_provider_offset();
    u64 tmp = dbg::ReadCheatProcessNso<u64>(offset);

    m_offset_item->setFocused(false);
    m_offset_item->setText(utils::num_to_hex(offset));

    m_tmp_item->setFocused(false);
    m_tmp_item->setText(utils::num_to_hex(tmp));
  }

  u64 get_player_prefs_provider_offset() {
    if (dbg::GetCheatProcessTitleId() == SupportedGame::BrilliantDiamond) {
      return bdsp::diamond::Offsets::PlayerPrefsProviderInstance;
    }

    return bdsp::pearl::Offsets::PlayerPrefsProviderInstance;
  }

  // u64 get_player_prefs_provider() {
  //   u64 offset = get_player_prefs_provider_offset();
  //   u64 tmp = dbg::ReadCheatProcessNso<u64>(offset);
  //   tmp = dbg::ReadCheatProcess<u64>(tmp + 0x18);
  //   tmp = dbg::ReadCheatProcess<u64>(tmp + 0xc0);
  //   tmp = dbg::ReadCheatProcess<u64>(tmp + 0x28);
  //   tmp = dbg::ReadCheatProcess<u64>(tmp + 0xb8);
  //   return dbg::ReadCheatProcess<u64>(tmp);
  // }

  // u64 get_daycare_addr() { return get_player_prefs_provider() + 0x450; }

 private:
  tsl::elm::ListItem *m_offset_item;
  tsl::elm::ListItem *m_tmp_item;
  tsl::elm::OverlayFrame *m_frame;
};

class CustomDaycareViewButton : public Button {
 public:
  CustomDaycareViewButton() : Button("Daycare view (Custom)") {
    this->onClick([]() { tsl::changeTo<CustomDaycareView>(); });
  }
};
