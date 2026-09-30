/* Address: 000102b8; name: FUN_000102b8; body bytes: 40 */

void FUN_000102b8(void)

{
  bool bVar1;
  char cVar2;
  undefined4 unaff_r8;
  undefined4 in_cr14;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setMainStackPointer(*DAT_e000ed08);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setThreadModePrivileged(1);
    bVar1 = (bool)isThreadMode();
    if (bVar1) {
      cVar2 = isUsingMainStack();
      setStackMode(cVar2 == '\x01');
    }
  }
  enableIRQinterrupts();
  enableFIQinterrupts();
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  software_interrupt(0);
  coprocessor_store(0,in_cr14,unaff_r8);
  DAT_e000ed88 = DAT_e000ed88 | 0xf00000;
  return;
}

