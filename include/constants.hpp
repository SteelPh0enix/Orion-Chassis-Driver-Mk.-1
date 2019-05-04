#pragma once

namespace Constant {
namespace Error {
constexpr char const ReadingChassisData[]{"{\"ERR\":1}"};
}

namespace Json {
constexpr char const LeftFrontWheelID[]{"0"};
constexpr char const LeftRearWheelID[]{"1"};
constexpr char const RightFrontWheelID[]{"2"};
constexpr char const RightRearWheelID[]{"3"};

constexpr char const Speed[]{"PWM"};
constexpr char const Temperature[]{"TMP"};
constexpr char const Current[]{"CUR"};

constexpr char const InputSpeed[]{"PWM"};
constexpr char const InputRotation[]{"ROT"};
}  // namespace Json
}  // namespace Constant