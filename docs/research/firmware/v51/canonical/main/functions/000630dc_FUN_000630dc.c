/* Address: 000630dc; name: FUN_000630dc; body bytes: 256 */

void FUN_000630dc(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_00046756();
  iVar1 = FUN_000527ec();
  if ((iVar1 == DAT_1ffe0534) && (current_mode == '\x01')) {
    if (DAT_1ffe02ac == 0) {
      DAT_1ffe0298 = 0;
      DAT_1ffe029c = 0;
      DAT_1fffabc0 = 0xffffffff;
      FUN_0001049c(&DAT_1fffacc0,800);
      FUN_0001049c(&DAT_1fffafe0,800);
      FUN_0001049c(&DAT_1fffb300,800);
      uVar2 = FUN_0004675a(param_1);
      DAT_1ffe02ac = FUN_0005285c(0x22059,100,uVar2);
    }
  }
  else if (DAT_1ffe02ac != 0) {
    FUN_000528ac();
    DAT_1ffe02ac = 0;
    DAT_1fffabc0 = 0xffffffff;
    uVar2 = FUN_0004675a(param_1);
    FUN_0003f926(uVar2,DAT_1ffe033c);
    uVar2 = FUN_0004675a(param_1);
    FUN_0003f926(uVar2,DAT_1ffe0338);
    uVar2 = FUN_0004037c(0xff00);
    DAT_1ffe033c = FUN_0003f4be(DAT_1ffe053c,uVar2,0);
    uVar2 = FUN_0004037c(0xffa600);
    DAT_1ffe0338 = FUN_0003f4be(DAT_1ffe053c,uVar2,1);
    uVar2 = FUN_0004675a(param_1);
    uVar2 = FUN_0004b9de(uVar2,0);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004675a(param_1);
    uVar2 = FUN_0004b9de(uVar2,1);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004675a(param_1);
    FUN_0003f960(uVar2,DAT_1ffe0340,0,0x7fffffff);
    FUN_0004675a(param_1);
    thunk_FUN_0004d3d8();
    return;
  }
  return;
}

