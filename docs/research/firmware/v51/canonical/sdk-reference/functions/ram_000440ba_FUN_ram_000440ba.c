/* Address: ram:000440ba; name: FUN_ram_000440ba; body bytes: 86 */

void FUN_ram_000440ba(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  
  gp = 0x20004000;
  uVar1 = 0;
  do {
    puVar3 = (undefined1 *)(param_1 + uVar1);
    do {
      uVar2 = uVar1;
      if (param_2 <= uVar2) {
        return;
      }
      uVar4 = tmos_rand();
      *puVar3 = (char)((ushort)uVar4 >> 8);
      uVar1 = uVar2 + 1 & 0xff;
      puVar3 = puVar3 + 1;
    } while (param_2 <= uVar1);
    *(char *)(uVar1 + param_1) = (char)uVar4;
    uVar1 = uVar2 + 2 & 0xff;
  } while( true );
}

