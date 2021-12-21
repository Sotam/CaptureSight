#pragma once

#include "../constants.hpp"
#include "./debug.hpp"
#include <atomic>
#include <csight-core.h>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <switch.h>
#include <tesla.hpp>

namespace utils {
  struct TrainerInfo {
    u16 sid;
    u16 tid;
  };

  std::shared_ptr<::utils::TrainerInfo> get_trainer_info(u32 sidtid) {
    return std::make_shared<::utils::TrainerInfo>(::utils::TrainerInfo {
      sid : (u16)(sidtid >> 16),
      tid : (u16)sidtid,
    });
  }

  template <typename T>
  std::string num_to_hex(T num) {
    std::ostringstream stream;
    stream << std::right << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << num;
    return stream.str();
  }

  template <typename T>
  std::string join(std::vector<T> items, std::string separator) {
    if (items.size() == 0) {
      return "";
    }

    std::string accumulator = std::to_string(items[0]);

    for (u32 i = 1; i < items.size(); i++) {
      accumulator += separator + std::to_string(items[i]);
    }

    return accumulator;
  }

  // Thanks to https://github.com/WerWolv/EdiZon/blob/44a30ce9ad2571f46c3e420faec44d573a27ebbc/source/helpers/util.c#L31-L42
  bool check_if_service_is_running(const char *serviceName) {
    Handle handle;
    SmServiceName service_name = smEncodeName(serviceName);
    bool running = R_FAILED(smRegisterService(&handle, service_name, false, 1));

    svcCloseHandle(handle);

    if (!running)
      smUnregisterService(service_name);

    return running;
  }

  std::shared_ptr<csight::Pkx> read_pkx(u64 address) {
    auto ek8 = dbg::ReadCheatProcessArray<u8, csight::Pk8::StoredSize>(address);
    return std::make_shared<csight::Pk8>(ek8);
  }

  std::atomic<bool> g_isAttached(false);

  bool getIsAttached() { return g_isAttached; }

  bool setIsAttached(bool attached) {
    g_isAttached = attached;
    tsl::hlp::requestForeground(attached);
    return g_isAttached;
  }

  bool toggleAttached() {
    bool isAttached = getIsAttached();
    return setIsAttached(!isAttached);
  }
}
