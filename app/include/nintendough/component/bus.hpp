#ifndef NINTENDOUGH_COMPONENT_BUS_HPP
#define NINTENDOUGH_COMPONENT_BUS_HPP

namespace nintendough::component {
class Bus {
 public:
  Bus() = default;
  virtual ~Bus() = default;
  Bus(Bus const &) = default;
  Bus(Bus &&) = default;
  Bus &operator=(Bus const &) = default;
  Bus &operator=(Bus &&) = default;
};
};  // namespace nintendough::component

#endif
