/* Address: 000273f8; name: FUN_000273f8; body bytes: 230 */

void FUN_000273f8(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  DAT_1fffabc4 = 0;
  FUN_0001814c();
  uVar4 = 0;
  while( true ) {
    iVar1 = FUN_0004ba5c(DAT_1ffe0718);
    if (iVar1 - 1U <= uVar4) break;
    uVar2 = FUN_0004b9de(DAT_1ffe0718,uVar4);
    FUN_0004dfd2(uVar2,0x2178d);
    uVar4 = uVar4 + 1 & 0xff;
  }
  uVar2 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe0700,uVar2);
  FUN_0004b288(DAT_1ffe0718);
  FUN_00021fe0(&DAT_000274f4,&DAT_0007f444);
  FUN_0004aaf6(DAT_1ffe0714,0x80);
  uVar2 = FUN_0004037c(0x333333);
  uVar3 = FUN_0004b9de(DAT_1ffe0714,0);
  FUN_0004e8e6(uVar3,uVar2,0);
  uVar2 = FUN_0004037c(0x333333);
  uVar3 = FUN_0004b9de(DAT_1ffe0714,0);
  uVar3 = FUN_0004b9de(uVar3,0);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar2 = FUN_0004037c(0x333333);
  uVar3 = FUN_0004b9de(DAT_1ffe0714,0);
  uVar3 = FUN_0004b9de(uVar3,1);
  FUN_0004e8b2(uVar3,uVar2,0);
  uVar2 = FUN_0004037c(0x333333);
  uVar3 = FUN_0004b9de(DAT_1ffe0714,1);
  FUN_0004ea90(uVar3,uVar2,0);
  FUN_00018114(DAT_1ffe0348);
  iVar1 = FUN_0004fe9c();
  if (iVar1 != DAT_1ffe0590) {
    FUN_0001cb8c(0xf);
    return;
  }
  return;
}

