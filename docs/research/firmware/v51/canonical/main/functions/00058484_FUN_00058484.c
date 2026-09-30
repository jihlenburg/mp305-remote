/* Address: 00058484; name: FUN_00058484; body bytes: 558 */

/* Recovered from stored Thumb pointer at 00021e98; callback identification is inferred until
   reviewed. */

void FUN_00058484(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 local_88 [18];
  int local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  bVar1 = false;
  uVar7 = 0;
  do {
    iVar5 = FUN_0004ba5c(DAT_1ffe05b0);
    if (iVar5 - 1U <= uVar7) {
LAB_000585fc:
      if (DAT_1ffe0330 == DAT_1ffe0468) {
        if (DAT_1fffab22 == '\0') {
          if (DAT_1fffab21 == '\x05') {
            FUN_0001974c();
          }
          else if (DAT_1fffab21 == '\x06') {
            FUN_0001976c();
          }
          else if (DAT_1fffab21 == '\b') {
            FUN_0001972c();
          }
          else if (current_mode == '\x03') {
            FUN_00013f14();
          }
        }
        else {
          DAT_1fffab1e = 1;
          FUN_0001ca60(200);
        }
      }
      if ((DAT_1fffaafb == '\x01') || (bVar1)) {
        local_38 = FUN_00037604();
        local_2c = 0x53975;
        uStack_34 = 0x23969;
        uStack_30 = 0x53c95;
        local_40 = DAT_1ffe0330;
        uStack_3c = 0;
        FUN_0001046a(local_88,&DAT_1fffbad0,0x48);
        puVar6 = &DAT_1fffbac0;
      }
      else {
        local_38 = FUN_000375f8();
        local_2c = 0x53975;
        uStack_34 = 0x2396d;
        uStack_30 = 0x53c95;
        local_40 = DAT_1ffe0330;
        uStack_3c = 0;
        FUN_0001046a(local_88,&DAT_1fffbb28,0x48);
        puVar6 = &DAT_1fffbb18;
      }
      FUN_00058430(*puVar6,puVar6[1],puVar6[2],puVar6[3]);
      return;
    }
    iVar5 = FUN_0004ba5c(DAT_1ffe05b0);
    if (((uVar7 < iVar5 - 4U) &&
        (iVar5 = FUN_0004b9de(DAT_1ffe05a8,uVar7 + 5), iVar5 == DAT_1ffe0330)) ||
       ((iVar5 = FUN_0004ba5c(DAT_1ffe05b0), iVar5 - 4U <= uVar7 &&
        (iVar5 = FUN_0004b9de(DAT_1ffe05a8,uVar7 + 4), iVar5 == DAT_1ffe0330)))) {
      bVar1 = true;
      uVar2 = FUN_0004037c(0);
      uVar3 = FUN_0004b9de(DAT_1ffe05b0,uVar7);
      FUN_0004e8b2(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_0004b9de(DAT_1ffe05b0,uVar7);
      FUN_0004ea90(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_0004b9de(DAT_1ffe05b0,uVar7);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e960(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0x999999);
      uVar3 = FUN_0004b9de(DAT_1ffe05b0,uVar7);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004ea90(uVar3,uVar2,0);
      goto LAB_000585fc;
    }
    if (((current_mode == '\x03') && (uVar4 = FUN_0004ba5c(DAT_1ffe0624), uVar7 < uVar4)) &&
       (iVar5 = FUN_0004b9de(DAT_1ffe0620,uVar7 + 4), iVar5 == DAT_1ffe0330)) {
      local_88[0] = FUN_0004037c(0);
      uVar2 = FUN_0004b9de(DAT_1ffe0624,uVar7);
      FUN_0004e8b2(uVar2,local_88[0],0);
      local_88[0] = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe0624,uVar7);
      FUN_0004ea90(uVar2,local_88[0],0);
      local_88[0] = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe0624,uVar7);
      uVar2 = FUN_0004b9de(uVar2,0);
      FUN_0004e960(uVar2,local_88[0],0);
      local_88[0] = FUN_0004037c(0x999999);
      uVar2 = FUN_0004b9de(DAT_1ffe0624,uVar7);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_0004ea90(uVar2,local_88[0],0);
    }
    uVar7 = uVar7 + 1 & 0xff;
  } while( true );
}

