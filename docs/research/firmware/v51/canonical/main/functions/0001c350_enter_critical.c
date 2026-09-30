/* Address: 0001c350; name: enter_critical; body bytes: 4 */

int enter_critical(void)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x50);
  }
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  DAT_1ffe0058 = DAT_1ffe0058 + 1;
  iVar2 = DAT_1ffe0058;
  if (DAT_1ffe0058 == 1) {
    iVar2 = DAT_e000ed04;
  }
  return iVar2;
}

