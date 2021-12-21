#pragma once

#include "../../components/button.hpp"
#include "../../utils/bdsp.hpp"
#include "../detachable-view.hpp"
#include "../pokemon-view.hpp"
#include <csight-core.h>
#include <memory>
#include <string>
#include <switch.h>
#include <tesla.hpp>
#include <vector>

static std::string getRoamerLabel(bdsp::Roamer *roamer) {
  // Limit the seed to 32 bits since only 32 bits are ever set
  return csight::Pkx::SpeciesString(roamer->species) + " Seed: " + utils::num_to_hex((u32)roamer->rng_seed);
}

class RoamerListView : public DetachableView {
 public:
  RoamerListView() : DetachableView("Roamer View") { }

  virtual void setupList(tsl::elm::List *list) {
    // We always need at least one item in a list to prevent it from crashing
    list->addItem(new tsl::elm::CategoryHeader("Pokemon"));

    auto roamers = bdsp::utils::read_roamers();

    for (auto roamer : roamers) {
      auto roamer_item = new tsl::elm::ListItem(getRoamerLabel(&roamer));
      list->addItem(roamer_item);
      m_roamer_items.push_back(roamer_item);
    }
  }

  virtual void update() {
    auto roamers = bdsp::utils::read_roamers();
    // The number of roamers won't change after the game starts,
    // but we'll lean on the side of caution.
    u32 size = std::min(roamers.size(), m_roamer_items.size());

    for (u32 i = 0; i < size; i++) {
      auto roamer_item = m_roamer_items[i];
      roamer_item->setFocused(false);
      roamer_item->setText(getRoamerLabel(&roamers[i]));
    }
  }

 private:
  std::vector<tsl::elm::ListItem *> m_roamer_items;
};

class RoamerListViewButton : public Button {
 public:
  RoamerListViewButton() : Button("Roamers") { this->onClick(tsl::changeTo<RoamerListView>); }
};
