#ifndef NINTENDOUGH_CPU_BUS_HPP
#define NINTENDOUGH_CPU_BUS_HPP

namespace nintendough::cpu {
class Bus {
 public:
  Bus() = default;
  virtual ~Bus() = default;
  Bus(Bus const &) = default;
  Bus(Bus &&) = default;
  Bus &operator=(Bus const &) = default;
  Bus &operator=(Bus &&) = default;


};
};  // namespace nintendough::cpu

#endif
