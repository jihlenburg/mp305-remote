/* Address: ram:000487a4; name: FUN_ram_000487a4; body bytes: 132 */

undefined4
FUN_ram_000487a4(int param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4,int param_5)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if (param_1 != 0xff) {
    puVar1 = (undefined1 *)tmos_msg_allocate(0x20);
    uVar2 = 0x13;
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 0xb0;
      puVar1[1] = param_3;
      *(undefined2 *)(puVar1 + 2) = param_2;
      puVar1[4] = param_4;
      if (param_5 == 0) {
        tmos_memset(puVar1 + 8,0,0x18);
      }
      else {
        tmos_memcpy(puVar1 + 8,param_5);
      }
      tmos_msg_send(param_1,puVar1);
      uVar2 = 0;
    }
    return uVar2;
  }
  return 2;
}

