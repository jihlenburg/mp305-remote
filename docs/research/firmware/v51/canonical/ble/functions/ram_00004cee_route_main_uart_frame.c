/* Address: ram:00004cee; name: route_main_uart_frame; body bytes: 234 */

/* Routes completed internal frames by destination type 6,1,5 or fallback. */

void route_main_uart_frame(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  gp = &DAT_ram_20002000;
  uVar3 = (uint)DAT_ram_20004770;
  for (uVar2 = 0; (uVar2 & 0xff) < uVar3; uVar2 = uVar2 + 1) {
    decode_main_uart_byte((&DAT_ram_20004670)[uVar2]);
  }
  if (DAT_ram_20004560 != '\0') {
    DAT_ram_20004560 = '\0';
    cVar1 = DAT_ram_20004565;
    if (DAT_ram_20004565 == '\x06') {
      uVar4 = FUN_ram_00003862(0);
      FUN_ram_000078b2(uVar4,&DAT_ram_20004564,0x104);
      DAT_ram_20002f8c = 1;
    }
    else if (DAT_ram_20004565 == '\x01') {
      uVar4 = FUN_ram_00003862(1);
      FUN_ram_000078b2(uVar4,&DAT_ram_20004564,0x104);
      DAT_ram_20002f8d = cVar1;
    }
    else if (DAT_ram_20004565 == '\x05') {
      uVar4 = FUN_ram_00003862(2);
      FUN_ram_000078b2(uVar4,&DAT_ram_20004564,0x104);
      DAT_ram_20002f8e = 1;
    }
    else {
      uVar4 = FUN_ram_00003862(3);
      FUN_ram_000078b2(uVar4,&DAT_ram_20004564,0x104);
      DAT_ram_20002f8f = 1;
    }
  }
  return;
}

