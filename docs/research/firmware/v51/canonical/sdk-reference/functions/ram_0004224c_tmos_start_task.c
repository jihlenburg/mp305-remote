/* Address: ram:0004224c; name: tmos_start_task; body bytes: 278 */

undefined4 tmos_start_task(uint param_1,undefined4 param_2,uint param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  uint uVar8;
  undefined1 *puVar9;
  
  pcVar1 = DAT_ram_20001c00;
  gp = 0x20004000;
  if (((param_1 < DAT_ram_20001b65) && (DAT_ram_20001c00 != (code *)0x0)) &&
     (uVar8 = DAT_ram_20001b8c * param_3, uVar3 = uVar8 + 800,
     uVar3 = FUN_ram_0006bae2(uVar3,(int)((ulonglong)(uint)DAT_ram_20001b8c * (ulonglong)param_3 >>
                                         0x20) + (uint)(uVar3 < uVar8),0x640,0), uVar3 < 0xa6f63c81)
     ) {
    iVar4 = (*pcVar1)();
    uVar8 = DAT_ram_20001b8c * param_3;
    uVar3 = uVar8 + 800;
    iVar5 = FUN_ram_0006bae2(uVar3,(int)((ulonglong)(uint)DAT_ram_20001b8c * (ulonglong)param_3 >>
                                        0x20) + (uint)(uVar3 < uVar8),0x640,0);
    uVar3 = iVar4 + iVar5;
    if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar3)) {
      uVar3 = uVar3 + 0x57400000;
    }
    iVar4 = FUN_ram_00041d8e(param_1,param_2);
    if (iVar4 == 0) {
      puVar6 = (undefined1 *)FUN_ram_20000040(0x10,(param_1 | 0xffffff00) & 0xffff);
      if (puVar6 == (undefined1 *)0x0) {
        if (DAT_ram_20001bec != (code *)0x0) {
          (*DAT_ram_20001bec)(4,param_1);
        }
        goto LAB_ram_0004226a;
      }
      puVar7 = DAT_ram_20001bb8;
      puVar9 = puVar6;
      if (DAT_ram_20001bb8 != (undefined1 *)0x0) {
        do {
          puVar9 = puVar7;
          puVar7 = *(undefined1 **)(puVar9 + 0xc);
        } while (puVar7 != (undefined1 *)0x0);
        *(undefined1 **)(puVar9 + 0xc) = puVar6;
        puVar9 = DAT_ram_20001bb8;
      }
      DAT_ram_20001bb8 = puVar9;
      *(undefined4 *)(puVar6 + 0xc) = 0;
      *(uint *)(puVar6 + 8) = uVar3;
      *(short *)(puVar6 + 2) = (short)param_2;
      *puVar6 = (char)param_1;
      puVar6[1] = 1;
      *(undefined4 *)(puVar6 + 4) = 0;
    }
    else {
      *(uint *)(iVar4 + 8) = uVar3;
    }
    uVar2 = 1;
  }
  else {
LAB_ram_0004226a:
    uVar2 = 0;
  }
  return uVar2;
}

