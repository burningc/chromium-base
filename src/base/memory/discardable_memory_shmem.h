// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_DISCARDABLE_MEMORY_SHMEM_H_
#define BASE_MEMORY_DISCARDABLE_MEMORY_SHMEM_H_

#include "base/memory/discardable_memory.h"

#include "base/memory/discardable_memory_manager.h"

namespace base {
class DiscardableMemoryShmemChunk;

namespace internal {

class DiscardableMemoryShmem
    : public DiscardableMemory,
      public internal::DiscardableMemoryManagerAllocation {
 public:
  explicit DiscardableMemoryShmem(size_t bytes);
  ~DiscardableMemoryShmem() override;

  static void ReleaseFreeMemory();

  static void PurgeForTesting();

  bool Initialize();

  // Overridden from DiscardableMemory:
  DiscardableMemoryLockStatus Lock() override;
  void Unlock() override;
  void* Memory() const override;

  // Overridden from internal::DiscardableMemoryManagerAllocation:
  bool AllocateAndAcquireLock() override;
  void ReleaseLock() override;
  void Purge() override;
  bool IsMemoryResident() const override;

 private:
  const size_t bytes_;
  scoped_ptr<DiscardableMemoryShmemChunk> chunk_;
  bool is_locked_;

  DISALLOW_COPY_AND_ASSIGN(DiscardableMemoryShmem);
};

}  // namespace internal
}  // namespace base

#endif  // BASE_MEMORY_DISCARDABLE_MEMORY_SHMEM_H_
