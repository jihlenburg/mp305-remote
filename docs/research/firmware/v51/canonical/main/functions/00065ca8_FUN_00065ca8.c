/* Address: 00065ca8; name: FUN_00065ca8; body bytes: 108 */

/* Recovered from stored Thumb pointer at 00053970; callback identification is inferred until
   reviewed. */

void FUN_00065ca8(void)

{
  undefined4 uVar1;
  ushort *puVar2;
  undefined4 uVar3;
  byte *pbVar4;
  
  uVar1 = FUN_00046698();
  FUN_0004bc8c();
  puVar2 = (ushort *)FUN_0003f334();
  uVar3 = FUN_0004b9de(uVar1,0);
  pbVar4 = (byte *)FUN_000461d4();
  FUN_000465d6(uVar3,((uint)pbVar4[3] + (*pbVar4 - 0x30) * 1000 +
                      (short)(ushort)pbVar4[1] * 100 + (uint)pbVar4[2] * 10 + -0x14d0) -
                     (uint)*puVar2);
  uVar1 = FUN_0004b9de(uVar1,1);
  FUN_000465d6(uVar1,(char)puVar2[1] + -1);
  return;
}

