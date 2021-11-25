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

  struct EggDetails {
    bool exists;
    u64 seed;
    s32 stepCount;
  };

 public:
  CustomDaycareView() : DetachableView("Daycare View (Custom)") { }

  virtual void setupList(tsl::elm::List *list) {
    list->addItem(new tsl::elm::CategoryHeader("Offset"));
    m_offset_item = new tsl::elm::ListItem("");
    list->addItem(m_offset_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP1"));
    m_tmp1_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp1_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP2"));
    m_tmp2_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp2_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP3"));
    m_tmp3_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp3_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP4"));
    m_tmp4_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp4_item);

    list->addItem(new tsl::elm::CategoryHeader("TMP5"));
    m_tmp5_item = new tsl::elm::ListItem("");
    list->addItem(m_tmp5_item);

    list->addItem(new tsl::elm::CategoryHeader("Prefs"));
    m_prefs_item = new tsl::elm::ListItem("");
    list->addItem(m_prefs_item);

    list->addItem(new tsl::elm::CategoryHeader("Day1"));
    m_daycare1_item = new tsl::elm::ListItem("");
    list->addItem(m_daycare1_item);

    list->addItem(new tsl::elm::CategoryHeader("Day2"));
    m_daycare2_item = new tsl::elm::ListItem("");
    list->addItem(m_daycare2_item);

    list->addItem(new tsl::elm::CategoryHeader("Seed"));
    m_seed_item = new tsl::elm::ListItem("");
    list->addItem(m_seed_item);

    list->addItem(new tsl::elm::CategoryHeader("Steps"));
    m_steps_item = new tsl::elm::ListItem("");
    list->addItem(m_steps_item);
  }

  virtual void handleInputIfAttached(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick,
                                     HidAnalogStickState rightJoyStick) { }

  virtual void update() {
    u64 offset = get_player_prefs_provider_offset();
    u64 tmp1 = dbg::ReadCheatProcessNso<u64>(offset);
    u64 tmp2 = dbg::ReadCheatProcess<u64>(tmp1 + 0x18);
    u64 tmp3 = dbg::ReadCheatProcess<u64>(tmp2 + 0xc0);
    u64 tmp4 = dbg::ReadCheatProcess<u64>(tmp3 + 0x28);
    u64 tmp5 = dbg::ReadCheatProcess<u64>(tmp4 + 0xb8);
    u64 get_player_prefs_provider = dbg::ReadCheatProcess<u64>(tmp5);

    u64 get_daycare_addr = get_player_prefs_provider + 0x450;

    EggDetails default_egg_details = {
      exists : false,
      seed : 0,
      stepCount : 0,
    };

    auto egg_details1 = dbg::ReadCheatProcess<EggDetails>(get_daycare_addr + 8, default_egg_details);
    auto egg_details = std::make_shared<EggDetails>(egg_details1);

    m_offset_item->setFocused(false);
    m_offset_item->setText(utils::num_to_hex(offset));

    m_tmp1_item->setFocused(false);
    m_tmp1_item->setText(utils::num_to_hex(tmp1));

    m_tmp2_item->setFocused(false);
    m_tmp2_item->setText(utils::num_to_hex(tmp2));

    m_tmp3_item->setFocused(false);
    m_tmp3_item->setText(utils::num_to_hex(tmp3));

    m_tmp4_item->setFocused(false);
    m_tmp4_item->setText(utils::num_to_hex(tmp4));

    m_tmp5_item->setFocused(false);
    m_tmp5_item->setText(utils::num_to_hex(tmp5));

    m_prefs_item->setFocused(false);
    m_prefs_item->setText(utils::num_to_hex(get_player_prefs_provider));

    m_daycare1_item->setFocused(false);
    m_daycare1_item->setText(utils::num_to_hex(get_daycare_addr));

    m_daycare2_item->setFocused(false);
    m_daycare2_item->setText(utils::num_to_hex(get_daycare_addr + 8));

    m_seed_item->setFocused(false);
    m_seed_item->setText(utils::num_to_hex(egg_details->seed));

    m_steps_item->setFocused(false);
    m_steps_item->setText(std::to_string(egg_details->stepCount));
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
  tsl::elm::ListItem *m_tmp1_item;
  tsl::elm::ListItem *m_tmp2_item;
  tsl::elm::ListItem *m_tmp3_item;
  tsl::elm::ListItem *m_tmp4_item;
  tsl::elm::ListItem *m_tmp5_item;
  tsl::elm::ListItem *m_prefs_item;
  tsl::elm::ListItem *m_daycare1_item;
  tsl::elm::ListItem *m_daycare2_item;
  tsl::elm::ListItem *m_seed_item;
  tsl::elm::ListItem *m_steps_item;
  tsl::elm::OverlayFrame *m_frame;
};

class CustomDaycareViewButton : public Button {
 public:
  CustomDaycareViewButton() : Button("Daycare view (Custom)") {
    this->onClick([]() { tsl::changeTo<CustomDaycareView>(); });
  }
};
