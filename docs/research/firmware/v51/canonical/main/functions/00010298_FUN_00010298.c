/* Address: 00010298; name: FUN_00010298; body bytes: 28 */

undefined4 FUN_00010298(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setProcessStackPointer(*DAT_1ffe0000 + 0x24);
  }
  InstructionSynchronizationBarrier(0xf);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return 0;
}

