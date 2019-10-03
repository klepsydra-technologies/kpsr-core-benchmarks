/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/

#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include <klepsydra/state_machine/state_machine.h>

namespace kpsr {
namespace fsm {
class StateMachineListener {
public:
  StateMachineListener(const std::string &stateMachineId = "");

  std::function<void(const std::string &currentState, bool stateChanged)>
  getObserverFunc();

  void addAction(const std::string &stateId,
                 std::function<void(const std::string &)> action);
  void addOneOffAction(const std::string &stateId,
                       std::function<void(const std::string &)> action);
  void addPeriodicAction(const std::string &stateId,
                         std::function<void(const std::string &)> action);
  void removeActions(const std::string &stateId);
  void removeActions();

private:
  void updateCurrentState(const std::string &currentStateId, bool stateChanged);
  std::unordered_map<std::string,
                     std::vector<std::function<void(const std::string &)>>>
      _actions;
  std::unordered_map<std::string,
                     std::vector<std::function<void(const std::string &)>>>
      _oneOffActions;
  std::unordered_map<std::string,
                     std::vector<std::function<void(const std::string &)>>>
      _periodicActions;
  std::string _stateMachineId;

  std::string getCompleteName(const std::string &stateId);
};
} // namespace fsm
} // namespace kpsr
