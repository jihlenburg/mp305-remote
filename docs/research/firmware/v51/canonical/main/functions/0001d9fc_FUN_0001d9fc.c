/* Address: 0001d9fc; name: FUN_0001d9fc; body bytes: 38 */

undefined4 FUN_0001d9fc(void)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x50);
  }
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  iVar2 = FUN_00066c28(0x50);
  if (iVar2 != 0) {
    DAT_e000ed04 = 0x10000000;
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return 0;
}

