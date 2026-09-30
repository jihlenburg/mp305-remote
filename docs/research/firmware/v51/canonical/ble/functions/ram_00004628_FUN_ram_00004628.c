/* Address: ram:00004628; name: FUN_ram_00004628; body bytes: 414 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00004628(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined2 uStack_14;
  
  gp = &DAT_ram_20002000;
  if (DAT_ram_20002f8c != '\0') {
    DAT_ram_20002f95 = '\x01';
    DAT_ram_20002f8c = '\0';
    route_main_reply_to_gatt(0);
  }
  if (DAT_ram_20002f8d != '\0') {
    DAT_ram_20002f95 = '\x01';
    DAT_ram_20002f8d = '\0';
    FUN_ram_00003d8a(1);
  }
  if (DAT_ram_20002f8e != '\0') {
    DAT_ram_20002f95 = '\x01';
    DAT_ram_20002f8e = '\0';
    FUN_ram_000045d4(2);
  }
  if (DAT_ram_20002f8f == '\0') {
    if (DAT_ram_20002f90 == 0) {
      if (DAT_ram_20003c58 == '\0') {
        if (DAT_ram_200042a0 == '\0' && DAT_ram_20004088 == '\0') {
          if (DAT_ram_20002f95 == '\0') {
            gp = &DAT_ram_20002000;
            return;
          }
          DAT_ram_200041a1 = (DAT_ram_20003a4a < 4) + -1;
          DAT_ram_200041a2 = -(DAT_ram_20002f88 != '\0');
          _DAT_ram_2000419c = 0x30203;
          DAT_ram_200041a0 = 0x55;
          uStack_1c = 0;
          uStack_18 = 0;
          uStack_14 = 0;
          uVar1 = encode_transport_frame(&DAT_ram_20004098,&DAT_ram_2000419c,&uStack_1c);
          thunk_FUN_ram_00002914(&uStack_1c,uVar1);
          gp = &DAT_ram_20002000;
          DAT_ram_20002f95 = 0;
          return;
        }
        if (DAT_ram_20004088 == '\0') {
          DAT_ram_200042a0 = '\0';
          uVar2 = 3;
        }
        else {
          DAT_ram_20004088 = '\0';
          uVar2 = 2;
        }
      }
      else {
        DAT_ram_20003c58 = '\0';
        uVar2 = 0;
      }
      FUN_ram_00003dd2(uVar2);
    }
    else {
      if (DAT_ram_20003e70 == '\0') {
        if (DAT_ram_20003a49 == '\0') {
          gp = &DAT_ram_20002000;
          return;
        }
        FUN_ram_00003c48();
      }
      else {
        DAT_ram_20003e70 = '\0';
        FUN_ram_00003dd2(1);
      }
      DAT_ram_20002f90 = 0;
    }
  }
  else {
    DAT_ram_20002f95 = '\x01';
    DAT_ram_20002f8f = '\0';
    dispatch_local_uart_command(thunk_FUN_ram_00002914);
  }
  return;
}

