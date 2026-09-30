/* Address: ram:00052316; name: FUN_ram_00052316; body bytes: 504 */

undefined4 FUN_ram_00052316(undefined2 param_1,int param_2,uint param_3,ushort *param_4)

{
  ushort uVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  
  gp = 0x20004000;
  if (param_2 == 2) {
    if (DAT_ram_20001a64 == '\0') {
      gp = 0x20004000;
      return 2;
    }
    DAT_ram_20001d5c = *param_4;
    if ((uint)DAT_ram_20001d5c == param_3 - 4) {
      puVar3 = (undefined2 *)tmos_msg_allocate(0xc);
      if (puVar3 != (undefined2 *)0x0) {
        *(undefined1 *)(puVar3 + 2) = 2;
        puVar3[3] = (short)param_3;
        uVar2 = (param_3 & 0xffff) + 5;
        *puVar3 = 0xff90;
        puVar3[1] = param_1;
        iVar4 = FUN_ram_20000040(uVar2,0x8001);
        *(int *)(puVar3 + 4) = iVar4;
        if (iVar4 != 0) {
          DAT_ram_20001a64 = DAT_ram_20001a64 + -1;
          FUN_ram_200001fc(iVar4,param_4 + -1,uVar2 >> 2);
          *(int *)(puVar3 + 4) = *(int *)(puVar3 + 4) + 2;
          tmos_msg_send(DAT_ram_20001cc8,puVar3);
          gp = 0x20004000;
          return 0;
        }
        FUN_ram_20000104(puVar3);
      }
    }
    else if ((int)(param_3 - 3) <= (int)(uint)DAT_ram_20001d5c) {
      if ((DAT_ram_20001a74 != '\0') && (DAT_ram_20001d58 != 0)) {
        FUN_ram_20000104();
      }
      DAT_ram_20001d58 = FUN_ram_20000040(DAT_ram_20001d5c + 4,0x8001);
      if (DAT_ram_20001d58 == 0) {
        gp = 0x20004000;
        return 1;
      }
      DAT_ram_20001a64 = DAT_ram_20001a64 + -1;
      tmos_memcpy(DAT_ram_20001d58,param_4,param_3);
      gp = 0x20004000;
      DAT_ram_20001a74 = 1;
      DAT_ram_20001d5e = (short)param_3;
      return 0;
    }
    DAT_ram_20001d5e = 0;
  }
  else {
    uVar2 = (uint)DAT_ram_20001d5e;
    if (uVar2 != 0) {
      if ((int)(uVar2 + param_3) <= (int)(DAT_ram_20001d5c + 4)) {
        tmos_memcpy(DAT_ram_20001d58 + uVar2,param_4);
        uVar2 = (uint)DAT_ram_20001d5e;
        DAT_ram_20001d5e = (ushort)((param_3 + uVar2) * 0x10000 >> 0x10);
        if ((param_3 + uVar2 & 0xffff) != DAT_ram_20001d5c + 4) {
          gp = 0x20004000;
          return 0;
        }
        puVar3 = (undefined2 *)tmos_msg_allocate(0xc);
        if (puVar3 != (undefined2 *)0x0) {
          *puVar3 = 0xff90;
          uVar1 = DAT_ram_20001d5e;
          puVar3[1] = param_1;
          *(undefined1 *)(puVar3 + 2) = 2;
          puVar3[3] = uVar1;
          *(int *)(puVar3 + 4) = DAT_ram_20001d58;
          tmos_msg_send(DAT_ram_20001cc8);
          gp = 0x20004000;
          DAT_ram_20001a74 = 0;
          DAT_ram_20001d5e = 0;
          return 0;
        }
        param_2 = 0;
      }
      if (DAT_ram_20001d58 != 0) {
        FUN_ram_20000104(DAT_ram_20001d58,param_2);
      }
      DAT_ram_20001d5e = 0;
      DAT_ram_20001a74 = '\0';
    }
  }
  return 1;
}

