/* Address: 00040d14; name: FUN_00040d14; body bytes: 878 */

undefined8
FUN_00040d14(float param_1,float param_2,int param_3,int param_4,int param_5,int param_6,int param_7
            ,int *param_8)

{
  short sVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  int iVar10;
  int iVar11;
  int local_38;
  int local_34;
  
  iVar10 = (int)param_1;
  local_34 = param_3 + param_5;
  iVar11 = (int)param_2;
  iVar7 = param_4 + param_5;
  local_38 = param_3;
  if (iVar11 == iVar10 + 0x168) {
LAB_00040d4c:
    *param_8 = param_3 - param_5;
    param_8[1] = param_4 - param_5;
    param_8[2] = local_34;
  }
  else {
    if (0x168 < iVar10) {
      iVar10 = iVar10 + -0x168;
    }
    if (0x168 < iVar11) {
      iVar11 = iVar11 + -0x168;
    }
    local_38 = param_5 - param_6;
    if (param_7 == 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = param_6 / 2 + 1;
    }
    uVar4 = iVar10 / 0x5a & 0xff;
    uVar6 = iVar11 / 0x5a & 0xff;
    if (uVar4 == 4) {
      uVar4 = 3;
    }
    if (uVar6 == 4) {
      uVar6 = 3;
    }
    sVar1 = (short)iVar10;
    sVar2 = (short)iVar11;
    if ((uVar4 == uVar6) && (iVar10 <= iVar11)) {
      if (uVar4 == 0) {
        iVar7 = thunk_FUN_00052d12((int)sVar1);
        param_8[1] = (param_4 + (local_38 * iVar7 >> 0xf)) - iVar8;
        iVar7 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
        param_8[2] = param_3 + (iVar7 * param_5 >> 0xf) + iVar8;
        iVar7 = thunk_FUN_00052d12((int)sVar2);
        param_8[3] = param_4 + (iVar7 * param_5 >> 0xf) + iVar8;
        iVar7 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
        iVar7 = local_38 * iVar7;
      }
      else {
        if (uVar4 != 1) {
          if (uVar4 == 2) {
            iVar7 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
            *param_8 = (param_3 + (iVar7 * param_5 >> 0xf)) - iVar8;
            iVar7 = thunk_FUN_00052d12((int)sVar1);
            param_8[3] = param_4 + (local_38 * iVar7 >> 0xf) + iVar8;
            iVar7 = thunk_FUN_00052d12((int)sVar2);
            param_8[1] = (param_4 + (iVar7 * param_5 >> 0xf)) - iVar8;
            iVar7 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
            param_8[2] = param_3 + (local_38 * iVar7 >> 0xf) + iVar8;
            goto LAB_00040e92;
          }
          if (uVar4 != 3) goto LAB_00040e92;
          iVar7 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
          *param_8 = (param_3 + (local_38 * iVar7 >> 0xf)) - iVar8;
          iVar7 = thunk_FUN_00052d12((int)sVar1);
          param_8[1] = (param_4 + (iVar7 * param_5 >> 0xf)) - iVar8;
          iVar7 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
          param_8[2] = param_3 + (iVar7 * param_5 >> 0xf) + iVar8;
          iVar7 = (int)sVar2;
LAB_0004103e:
          iVar7 = thunk_FUN_00052d12(iVar7);
          iVar7 = local_38 * iVar7;
          goto LAB_00041048;
        }
        iVar7 = thunk_FUN_00052d12((int)sVar1);
        param_8[3] = param_4 + (iVar7 * param_5 >> 0xf) + iVar8;
        iVar7 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
        param_8[2] = param_3 + (local_38 * iVar7 >> 0xf) + iVar8;
        iVar7 = thunk_FUN_00052d12((int)sVar2);
        param_8[1] = (param_4 + (local_38 * iVar7 >> 0xf)) - iVar8;
        iVar7 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
        iVar7 = iVar7 * param_5;
      }
      *param_8 = (param_3 + (iVar7 >> 0xf)) - iVar8;
      goto LAB_00040e92;
    }
    if (uVar4 == 0) {
      bVar9 = uVar6 == 1;
      if (!bVar9) goto LAB_00040efa;
      iVar10 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
      *param_8 = (param_3 + (iVar10 * param_5 >> 0xf)) - iVar8;
      local_34 = (int)sVar2;
      iVar11 = thunk_FUN_00052d12();
      iVar10 = (int)sVar1;
      iVar5 = thunk_FUN_00052d12(iVar10);
      if (iVar11 < iVar5) {
        iVar10 = local_34;
      }
      iVar10 = thunk_FUN_00052d12(iVar10);
      param_8[1] = (param_4 + (local_38 * iVar10 >> 0xf)) - iVar8;
      iVar10 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
      param_8[2] = param_3 + (iVar10 * param_5 >> 0xf) + iVar8;
    }
    else {
      if (uVar4 == 1) {
        bVar9 = uVar6 == 2;
        if (!bVar9) goto LAB_00040efa;
        *param_8 = (param_3 - param_5) - iVar8;
        iVar7 = thunk_FUN_00052d12((int)sVar2);
        param_8[1] = (param_4 + (iVar7 * param_5 >> 0xf)) - iVar8;
        local_34 = (int)(short)(sVar1 + 0x5a);
        iVar10 = thunk_FUN_00052d12();
        iVar7 = (int)(short)(sVar2 + 0x5a);
        iVar11 = thunk_FUN_00052d12(iVar7);
        if (iVar11 < iVar10) {
          iVar7 = local_34;
        }
        iVar7 = thunk_FUN_00052d12(iVar7);
        param_8[2] = param_3 + (local_38 * iVar7 >> 0xf) + iVar8;
      }
      else {
        if (uVar4 == 2) {
          bVar9 = false;
          if (uVar6 == 3) {
            iVar7 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
            *param_8 = (param_3 + (iVar7 * param_5 >> 0xf)) - iVar8;
            param_8[1] = (param_4 - param_5) - iVar8;
            iVar7 = thunk_FUN_00052d12((int)(short)(sVar2 + 0x5a));
            param_8[2] = param_3 + (iVar7 * param_5 >> 0xf) + iVar8;
            iVar10 = thunk_FUN_00052d12((int)sVar2);
            iVar7 = (int)sVar1;
            iVar11 = thunk_FUN_00052d12(iVar7);
            if (iVar10 * local_38 - local_38 * iVar11 != 0 && local_38 * iVar11 <= iVar10 * local_38
               ) {
              iVar7 = (int)sVar2;
            }
            goto LAB_0004103e;
          }
        }
        else {
          bVar9 = uVar4 == 3;
        }
LAB_00040efa:
        do {
          if (!bVar9) goto LAB_00040d4c;
          bVar9 = uVar6 == 0;
        } while (!bVar9);
        iVar7 = thunk_FUN_00052d12();
        iVar10 = thunk_FUN_00052d12();
        sVar3 = sVar1;
        if (iVar7 < iVar10) {
          sVar3 = sVar2;
        }
        iVar7 = thunk_FUN_00052d12((int)(short)(sVar3 + 0x5a));
        *param_8 = (param_3 + (local_38 * iVar7 >> 0xf)) - iVar8;
        iVar7 = thunk_FUN_00052d12((int)sVar1);
        param_8[1] = (param_4 + (iVar7 * param_5 >> 0xf)) - iVar8;
        param_8[2] = local_34 + iVar8;
        sVar1 = sVar2;
      }
      iVar7 = thunk_FUN_00052d12((int)sVar1);
      iVar7 = iVar7 * param_5;
LAB_00041048:
      iVar7 = param_4 + (iVar7 >> 0xf);
    }
    iVar7 = iVar7 + iVar8;
  }
  param_8[3] = iVar7;
LAB_00040e92:
  return CONCAT44(local_34,local_38);
}

