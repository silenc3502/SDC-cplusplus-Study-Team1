//
// Created by eddi on 23. 12. 4.
//

#ifndef CLASS_TEST_UISERVICE_H
#define CLASS_TEST_UISERVICE_H

#include <vector>
#include "handler/create/UiServiceCreateHandler.h"
#include "handler/exit/UiServiceExitHandler.h"
#include "handler/list/UiServiceListHandler.h"
#include "handler/modify/UiServiceModifyHandler.h"
#include "handler/read/UiServiceReadHandler.h"
#include "handler/remove/UiServiceRemoveHandler.h"

class UiService {
public:
    virtual ~UiService() = default;
    virtual std::vector<UiServiceCreateHandler> UiServiceCreateHandler() = 0;
    virtual std::vector<UiServiceExitHandler> UiServiceExitHandler() = 0;
    virtual std::vector<UiServiceListHandler> UiServiceListHandler() = 0;
    virtual std::vector<UiServiceModifyHandler> UiServiceModifyHandler() = 0;
    virtual std::vector<UiServiceReadHandler> UiServiceReadHandler() = 0;
    virtual std::vector<UiServiceRemoveHandler> UiServiceRemoveHandler() = 0;
};

#endif //CLASS_TEST_UISERVICE_H