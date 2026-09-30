/* Address: ram:000511fe; name: FUN_ram_000511fe; body bytes: 56 */

void FUN_ram_000511fe(int param_1,int param_2,uint param_3)

{
  undefined1 *puVar1;
  uint uVar2;
  
  gp = 0x20004000;
  uVar2 = 0;
  do {
    puVar1 = (undefined1 *)(param_2 + uVar2);
    if ((uVar2 & 0xff) < param_3) {
      *puVar1 = *(undefined1 *)(param_1 + uVar2);
    }
    else if ((uVar2 & 0xff) == param_3) {
      *puVar1 = 0x80;
    }
    else {
      *puVar1 = 0;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x10);
  return;
}

