/* Address: 00036b48; name: FUN_00036b48; body bytes: 102 */

undefined4 FUN_00036b48(void)

{
  bool bVar1;
  int iVar2;
  undefined4 unaff_r4;
  
  FUN_00066ba4(0x1d7a1,"Start_Task",0x80,0,1,&DAT_1ffe0228);
  iVar2 = FUN_00066ba4(0x59ae9,&DAT_00065bf8,0x82,0,0,&DAT_1ffe002c,unaff_r4);
  if ((iVar2 == 1) && (iVar2 = FUN_00067090(), iVar2 == 1)) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x50);
    }
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
    DAT_1ffe0028 = 0xffffffff;
    DAT_1ffe0014 = 1;
    DAT_1ffe000c = 0;
    FUN_00066608();
  }
  return DAT_1ffe0030;
}

