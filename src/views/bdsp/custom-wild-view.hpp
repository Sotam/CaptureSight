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

class CustomWildView : public DetachableView {

 public:
  CustomWildView() : DetachableView("Wild View (Custom)") { }

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

    list->addItem(new tsl::elm::CategoryHeader("TMP6"));
    m_prefs_item = new tsl::elm::ListItem("");
    list->addItem(m_prefs_item);

    list->addItem(new tsl::elm::CategoryHeader("EK8"));
    m_daycare1_item = new tsl::elm::ListItem("");
    list->addItem(m_daycare1_item);
  }

  virtual void handleInputIfAttached(u64 keysDown, u64 keysHeld, const HidTouchState &touchPos, HidAnalogStickState leftJoyStick,
                                     HidAnalogStickState rightJoyStick) { }

  virtual void update() {

    // read_wild_pokemon
    u64 address = get_battle_setup_param_addr();
    u64 tmp1 = dbg::ReadCheatProcess<u64>(address + 0x58);
    u64 tmp2 = dbg::ReadCheatProcess<u64>(tmp1 + 0x28);
    // u64 read_pokemon_in_party = tmp2;

    // read_pokemon_in_party
    u64 tmp3 = dbg::ReadCheatProcess<u64>(tmp2 + 0x10);
    u64 tmp4 = dbg::ReadCheatProcess<u64>(tmp3 + 0x20 + (8 * 0));
    // return read_pokemon_from_poke_param(tmp4);

    // read_pokemon_from_poke_param
    u64 tmp5 = dbg::ReadCheatProcess<u64>(tmp4 + 0x20);
    u64 tmp6 = dbg::ReadCheatProcess<u64>(tmp5 + 0x18);
    // return ::utils::read_pkx(tmp6 + 0x20);

    // read_pkx
    auto ek8 = dbg::ReadCheatProcessArray<u8, csight::Pk8::StoredSize>(tmp6 + 0x20);

    m_offset_item->setFocused(false);
    m_offset_item->setText(utils::num_to_hex(address));

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
    m_prefs_item->setText(utils::num_to_hex(tmp6));

    m_daycare1_item->setFocused(false);
    m_daycare1_item->setText(utils::num_to_hex(ek8));
  }

  std::shared_ptr<csight::Pkx> read_wild_pokemon() {
    u64 address = get_battle_setup_param_addr();
    u64 tmp = dbg::ReadCheatProcess<u64>(address + 0x58);
    tmp = dbg::ReadCheatProcess<u64>(tmp + 0x28);
    return read_pokemon_in_party(tmp, 0);
  }

  u64 get_battle_setup_param_addr() { return dbg::ReadCheatProcess<u64>(get_player_prefs_provider() + 0x7e8); }

  u64 get_player_prefs_provider() {
    u64 tmp = dbg::ReadCheatProcessNso<u64>(bdsp::Offsets::PlayerPrefsProviderInstance);
    tmp = dbg::ReadCheatProcess<u64>(tmp + 0x18);
    tmp = dbg::ReadCheatProcess<u64>(tmp + 0xc0);
    tmp = dbg::ReadCheatProcess<u64>(tmp + 0x28);
    tmp = dbg::ReadCheatProcess<u64>(tmp + 0xb8);
    return dbg::ReadCheatProcess<u64>(tmp);
  }

 private:
  tsl::elm::ListItem *m_offset_item;
  tsl::elm::ListItem *m_tmp1_item;
  tsl::elm::ListItem *m_tmp2_item;
  tsl::elm::ListItem *m_tmp3_item;
  tsl::elm::ListItem *m_tmp4_item;
  tsl::elm::ListItem *m_tmp5_item;
  tsl::elm::ListItem *m_prefs_item;
  tsl::elm::ListItem *m_daycare1_item;
  tsl::elm::OverlayFrame *m_frame;
};

class CustomWildViewButton : public Button {
 public:
  CustomWildViewButton() : Button("Wild view (Custom)") {
    this->onClick([]() { tsl::changeTo<CustomWildView>(); });
  }
};
