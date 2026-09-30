/* Address: 000564b4; name: FUN_000564b4; body bytes: 100 */

void FUN_000564b4(void)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = FUN_0004b9de(DAT_1ffe05b0,0);
  uVar2 = FUN_0004b9de(uVar2,1);
  FUN_000499de(uVar2,&DAT_00056508,(&DAT_1ffe0778)[DAT_1ffe032c]);
  uVar2 = FUN_0004037c(0xffa600);
  uVar3 = FUN_0004b9de(DAT_1ffe06cc,DAT_1ffe032c);
  FUN_0004e8b2(uVar3,uVar2,0);
  bVar1 = DAT_1fffaaf9;
  enter_critical();
  DAT_1fffa9d6 = (ushort)bVar1 * 10;
  exit_critical();
  return;
}

