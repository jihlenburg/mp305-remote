/* Address: ram:0004d198; name: FUN_ram_0004d198; body bytes: 94 */

undefined4 FUN_ram_0004d198(undefined4 param_1,undefined2 param_2,int param_3)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0xc);
  if (puVar1 == (undefined2 *)0x0) {
    uVar2 = 1;
  }
  else {
    *puVar1 = 0xa0;
    puVar1[1] = param_2;
    if (param_3 == 0) {
      tmos_memset(puVar1 + 2,0,8);
    }
    else {
      tmos_memcpy(puVar1 + 2,param_3);
    }
    tmos_msg_send(param_1,puVar1);
    uVar2 = 0;
  }
  return uVar2;
}

