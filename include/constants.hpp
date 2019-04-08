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

constexpr char const Speed[]{"SPD"};
constexpr char const Temperature[]{"TEMP"};
constexpr char const Current[]{"CURR"};

constexpr char const InputSpeed[]{"SPD"};
constexpr char const InputRotation[]{"ROT"};
}  // namespace Json
}  // namespace Constant