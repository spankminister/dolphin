// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>

#include "Common/CommonTypes.h"
#include "Core/IOS/Device.h"
#include "Core/IOS/IPC.h"

class PointerWrap;

namespace IOS
{
namespace HLE
{
struct NANDStat
{
  u32 BlockSize;
  u32 FreeUserBlocks;
  u32 UsedUserBlocks;
  u32 FreeSysBlocks;
  u32 UsedSysBlocks;
  u32 Free_INodes;
  u32 Used_Inodes;
};

namespace Device
{
class FS : public Device
{
public:
  FS(u32 device_id, const std::string& device_name);

  void DoState(PointerWrap& p) override;

  ReturnCode Open(const OpenRequest& request) override;
  IPCCommandResult IOCtl(const IOCtlRequest& request) override;
  IPCCommandResult IOCtlV(const IOCtlVRequest& request) override;

private:
  enum
  {
    IOCTL_GET_STATS = 0x02,
    IOCTL_CREATE_DIR = 0x03,
    IOCTLV_READ_DIR = 0x04,
    IOCTL_SET_ATTR = 0x05,
    IOCTL_GET_ATTR = 0x06,
    IOCTL_DELETE_FILE = 0x07,
    IOCTL_RENAME_FILE = 0x08,
    IOCTL_CREATE_FILE = 0x09,
    IOCTLV_GETUSAGE = 0x0C,
    IOCTL_SHUTDOWN = 0x0D
  };

  IPCCommandResult GetFSReply(s32 return_value) const;
  s32 ExecuteCommand(const IOCtlRequest& request);
};
}  // namespace Device
}  // namespace HLE
}  // namespace IOS
