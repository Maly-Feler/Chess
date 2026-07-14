#pragma once
#include "CellPos.hpp"

enum class ClickAction {
    None,
    Selected,
    Reselected,
    MoveRequest,
    JumpRequest
};

struct ClickResult {
    ClickAction action = ClickAction::None;
    CellPos from = {0, 0, false};
    CellPos to   = {0, 0, false};
};