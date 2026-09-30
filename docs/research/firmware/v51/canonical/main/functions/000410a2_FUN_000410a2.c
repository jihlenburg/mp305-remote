/* Address: 000410a2; name: FUN_000410a2; body bytes: 258 */

undefined4 FUN_000410a2(uint *param_1,uint param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  if (param_1 == (uint *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_1[4] == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar5 = param_1[1] & 0xffff;
  uVar4 = param_1[1] >> 0x10;
  if ((int)((*param_1 >> 0x10) << 0x1a) < 0) {
    if (param_2 == 0) {
      param_2 = FUN_00041788(uVar5,(*param_1 & 0xffff) >> 8);
    }
    if ((ushort)param_1[2] != param_2) {
      iVar3 = FUN_00040314((ushort)*param_1 >> 8);
      uVar7 = uVar5 * iVar3 + 7 >> 3;
      if ((param_2 < uVar7) ||
         (uVar5 = FUN_00020316(uVar5,uVar4,(ushort)*param_1 >> 8,param_2), param_1[3] < uVar5))
      goto LAB_0004110c;
      uVar1 = (ushort)*param_1 >> 8;
      if (uVar1 == 7) {
        iVar3 = 2;
      }
      else if (uVar1 == 8) {
        iVar3 = 4;
      }
      else if (uVar1 == 9) {
        iVar3 = 0x10;
      }
      else if (uVar1 == 10) {
        iVar3 = 0x100;
      }
      else {
        iVar3 = 0;
      }
      iVar3 = iVar3 * 4;
      if ((ushort)param_1[2] < param_2) {
        iVar6 = (uint)(ushort)param_1[2] * (uVar4 - 1) + param_1[4] + iVar3;
        iVar3 = iVar3 + param_2 * (uVar4 - 1) + param_1[4];
        for (uVar5 = 0; uVar5 < uVar4; uVar5 = uVar5 + 1) {
          FUN_0004a538(iVar3,iVar6,uVar7);
          iVar3 = iVar3 - param_2;
          iVar6 = iVar6 - (uint)(ushort)param_1[2];
        }
      }
      else {
        iVar3 = iVar3 + param_1[4];
        iVar6 = iVar3;
        for (uVar5 = 0; uVar5 < uVar4; uVar5 = uVar5 + 1) {
          FUN_0004a538(iVar3,iVar6,uVar7);
          iVar6 = iVar6 + (param_1[2] & 0xffff);
          iVar3 = iVar3 + param_2;
        }
      }
      *(ushort *)(param_1 + 2) = (ushort)param_2;
    }
    uVar2 = 1;
  }
  else {
LAB_0004110c:
    uVar2 = 0;
  }
  return uVar2;
}

