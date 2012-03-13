/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of <UnNamedToolKit>                                 //
//                                                                          //
//  <UnNamedToolKit> is free software: you can redistribute it and/or modify//
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
// <UnNamedToolKit> is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Save.h"
#include <QObject>
#include <QFile>
#include <QDataStream>

bool FF7Save::LoadFile(const QString &fileName)
{
    // Return true if File Loaded and false if file not loaded.
    // This Class should contain NO Gui Parts
    if(fileName.isEmpty()){return false;}// bail on empty string.
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){return false;}
    QByteArray ff7file;
    ff7file = file.readAll(); //put all data in temp raw file
    QByteArray temp; // create a temp to be used when needed
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int file_size = file.size();
    //decide the file type
    if((file_size == FF7_PC_SAVE_GAME_SIZE) && ff7file.startsWith(PC_SAVE_GAME_FILE_ID)){setType("PC");}
    else if((file_size == FF7_PSX_SAVE_GAME_SIZE)&& ff7file.startsWith(PSX_SAVE_GAME_FILE_ID)){setType("PSX");}
    else if((file_size == FF7_MC_SAVE_GAME_SIZE) && ff7file.startsWith(MC_SAVE_GAME_FILE_ID)){setType("MC");}
    else if((file_size == FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith(PSV_SAVE_GAME_FILE_ID)){setType("PSV");}
    else if((file_size ==FF7_PSP_SAVE_GAME_SIZE) && ff7file.startsWith(PSP_SAVE_GAME_FILE_ID)){setType("PSP");}
    else if((file_size ==FF7_VGS_SAVE_GAME_SIZE) && ff7file.startsWith(VGS_SAVE_GAME_FILE_ID)){setType("VGS");}
    else if((file_size ==FF7_DEX_SAVE_GAME_SIZE) && ff7file.startsWith(DEX_SAVE_GAME_FILE_ID)){setType("DEX");}
    else{return false;}
    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    memcpy(file_headerp,ff7file.mid(0x0000,SG_HEADER),SG_HEADER);// collect header (0x09) bytes (PC), (0x00) bytes (PSX), (0x2000) bytes (MC)
    for (int i=0;i<SG_SLOT_NUMBER;i++)
    {
        int index = (SG_SLOT_SIZE*i) + SG_HEADER + SG_SLOT_HEADER;
        memcpy(hf[i].sl_header,ff7file.mid((SG_SLOT_SIZE*i) + (SG_HEADER + 0x0000),SG_SLOT_HEADER),SG_SLOT_HEADER);// collect slot header (0x00) bytes (PC), (0x0200) bytes (PSX), (0x0200) bytes (MC)
        temp = ff7file.mid(index,0x10f4);
        memcpy(&slot[i],temp,0x10f4);
        memcpy(hf[i].sl_footer,ff7file.mid((SG_SLOT_SIZE*i)+ (SG_HEADER+SG_SLOT_HEADER+SG_DATA_SIZE),SG_SLOT_FOOTER),SG_SLOT_FOOTER);// collect slot footer (0x00) bytes (PC), (0x0D0C) bytes (PSX), (0x0D0C) bytes (MC)
    }
    memcpy(file_footerp,ff7file.mid(((SG_SLOT_SIZE*SG_SLOT_NUMBER) + SG_HEADER + SG_SLOT_HEADER),SG_FOOTER),SG_FOOTER);// LOAD FOOTER IF ITS THERE>! FIX INDEX.
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/
    if (SG_TYPE == "PC")
    {
        if(slot[0].checksum != 0x0000 && slot[0].checksum != 0x4D1D){SG_Region_String[0]= "BASCUS-94163FF7-S01";} else {SG_Region_String[0].clear();}
        if(slot[1].checksum != 0x0000 && slot[1].checksum != 0x4D1D){SG_Region_String[1]= "BASCUS-94163FF7-S02";} else {SG_Region_String[1].clear();}
        if(slot[2].checksum != 0x0000 && slot[2].checksum != 0x4D1D){SG_Region_String[2]= "BASCUS-94163FF7-S03";} else {SG_Region_String[2].clear();}
        if(slot[3].checksum != 0x0000 && slot[3].checksum != 0x4D1D){SG_Region_String[3]= "BASCUS-94163FF7-S04";} else {SG_Region_String[3].clear();}
        if(slot[4].checksum != 0x0000 && slot[4].checksum != 0x4D1D){SG_Region_String[4]= "BASCUS-94163FF7-S05";} else {SG_Region_String[4].clear();}
        if(slot[5].checksum != 0x0000 && slot[5].checksum != 0x4D1D){SG_Region_String[5]= "BASCUS-94163FF7-S06";} else {SG_Region_String[5].clear();}
        if(slot[6].checksum != 0x0000 && slot[6].checksum != 0x4D1D){SG_Region_String[6]= "BASCUS-94163FF7-S07";} else {SG_Region_String[6].clear();}
        if(slot[7].checksum != 0x0000 && slot[7].checksum != 0x4D1D){SG_Region_String[7]= "BASCUS-94163FF7-S08";} else {SG_Region_String[7].clear();}
        if(slot[8].checksum != 0x0000 && slot[8].checksum != 0x4D1D){SG_Region_String[8]= "BASCUS-94163FF7-S09";} else {SG_Region_String[8].clear();}
        if(slot[9].checksum != 0x0000 && slot[9].checksum != 0x4D1D){SG_Region_String[9]= "BASCUS-94163FF7-S10";} else {SG_Region_String[9].clear();}
        if(slot[10].checksum != 0x0000 && slot[10].checksum != 0x4D1D){SG_Region_String[10]= "BASCUS-94163FF7-S11";} else {SG_Region_String[10].clear();}
        if(slot[11].checksum != 0x0000 && slot[11].checksum != 0x4D1D){SG_Region_String[11]= "BASCUS-94163FF7-S12";} else {SG_Region_String[11].clear();}
        if(slot[12].checksum != 0x0000 && slot[12].checksum != 0x4D1D){SG_Region_String[12]= "BASCUS-94163FF7-S13";} else {SG_Region_String[12].clear();}
        if(slot[13].checksum != 0x0000 && slot[13].checksum != 0x4D1D){SG_Region_String[13]= "BASCUS-94163FF7-S14";} else {SG_Region_String[13].clear();}
        if(slot[14].checksum != 0x0000 && slot[14].checksum != 0x4D1D){SG_Region_String[14]= "BASCUS-94163FF7-S15";} else {SG_Region_String[14].clear();}
    }

    else if (SG_TYPE == "PSX")
    {
        if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
           (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) ||
           (fileName.contains("00868")))
        {
            QString string;
            string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
            SG_Region_String[0]= string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8);
        }
        else {SG_Region_String[0].clear();}
        for(int i=1;i<14;i++){clearslot(i);}
    }

    else if (SG_TYPE =="PSV")
    {
        SG_Region_String[0] = QString(ff7file.mid(0x64,19));
        for(int i=1;i<14;i++){clearslot(i);}
    }

    else if (SG_TYPE == "MC" || SG_TYPE =="PSP" || SG_TYPE == "VGS" ||SG_TYPE=="DEX")
    {
        QByteArray mc_header;
        int offset = 0;//raw psx card types
        if(SG_TYPE =="PSP"){offset = 0x80;}
        if(SG_TYPE =="VGS"){offset = 0x40;}
        if(SG_TYPE =="DEX"){offset = 0xF40;}
        mc_header = ff7file.mid(offset,SG_HEADER);
        int index=0;
        for(int i=0; i<15;i++)
        {
            index = (128*i) +138;
            setRegion(i,QString(mc_header.mid(index,19)));
        }
    }
    else{return false;}
    return true;
}
bool FF7Save::SaveFile(const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    //fix our headers before saving
    if(type() =="PC"){/*FIX PC BYTEMASK SHOULD BE CALLED BY HOST*/}
    else if(type() == "PSX"){fix_psx_header(0);}
    else if(type() =="PSV"){fix_psv_header();}
    else{fix_vmc_header();}
    // write the file
    FILE *pfile;
    pfile = fopen(fileName.toAscii(),"wb");
    if(pfile == NULL){return false;}
    fwrite(file_headerp,SG_HEADER,1,pfile);
    for(int si=0;si<SG_SLOT_NUMBER;si++)
    {
        fwrite(hf[si].sl_header,SG_SLOT_HEADER,1,pfile);
        fwrite(&slot[si],SG_DATA_SIZE,1,pfile);
        fwrite(hf[si].sl_footer,SG_SLOT_FOOTER,1,pfile);
    }
    fwrite(file_footerp,SG_FOOTER,1,pfile);
    fclose(pfile);
    fix_sum(fileName);
    return true;
}
bool FF7Save::Export_PC(const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    QString prev_type = SG_TYPE;
    if(SG_TYPE !="PC")
    {
      /*RESET CONTROLLS LATER WHEN IMPLIMENTED!!!*/
      setType("PC");
      // Add File Header
      for(int i=0;i<9;i++){file_header_pc[i]= PC_SAVE_GAME_FILE_HEADER[i];}
      fix_pc_bytemask(0);//set first slot to 0
    }
    for(int i=0;i<15;i++)//clean up saves and fix time for Pal Saves.
    {
      if (isNTSC(i)){/*NTSC FF7 DATA.*/}
      else if(isPAL(i))
      {//PAL FF7 DATA , FIX PLAY TIME THEN SAVE
        slot[i].time = (slot[i].time*1.2);
        slot[i].desc.time = slot[i].time;
      }
      else{clearslot(i);}
    }
    if(SaveFile(fileName))
    {
        setType(prev_type);
        return true;
    }
    else
    {
        setType(prev_type);
        return false;
    }
}
bool FF7Save::Export_PSX(const QString &fileName)
{
    if(fileName.isEmpty()){return false;}
    QString prev_type = SG_TYPE;
    if(SG_TYPE != "PSX")
    {
        /*RESET CONTROLLS LATER WHEN IMPLIMENTED!!!*/
        setType("PSX");
    }
    if(fileName.contains("00867") || fileName.contains("00869") ||
       fileName.contains("00900") || fileName.contains("94163") ||
       fileName.contains("00700") || fileName.contains("01057") ||
       fileName.contains("00868"))
    {
        if(fileName.endsWith("S01")){for(int i=0;i<256;i++)	  {hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S01[i];}}
        else if(fileName.endsWith("S02")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S02[i];}}
        else if(fileName.endsWith("S03")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S03[i];}}
        else if(fileName.endsWith("S04")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S04[i];}}
        else if(fileName.endsWith("S05")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S05[i];}}
        else if(fileName.endsWith("S06")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S06[i];}}
        else if(fileName.endsWith("S07")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S07[i];}}
        else if(fileName.endsWith("S08")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S08[i];}}
        else if(fileName.endsWith("S09")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S09[i];}}
        else if(fileName.endsWith("S10")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S10[i];}}
        else if(fileName.endsWith("S11")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S11[i];}}
        else if(fileName.endsWith("S12")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S12[i];}}
        else if(fileName.endsWith("S13")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S13[i];}}
        else if(fileName.endsWith("S14")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S14[i];}}
        else if(fileName.endsWith("S15")){for(int i=0;i<256;i++){hf[0].sl_header[i] = PSX_SAVE_GAME_FILE_HEADER_S15[i];}}
        else{/*user ERROR*/}
        for(int i=0; i<SG_SLOT_FOOTER;i++){hf[0].sl_footer[i] =0x00;} //CLEAN FOOTER
    }
    fix_psx_header(0);
    if(SaveFile(fileName))
    {
        setType(prev_type);
        return true;
    }
    else
    {
        setType(prev_type);
        return false;
    }
}
bool FF7Save::Export_VMC(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "MC")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    setType("MC");
  }
  fix_vmc_header();
  if(SaveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
bool FF7Save::Export_VGS(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "VGS")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
    setType("VGS");//fill the Header With The Needed Default
    file_header_vgs[0] =0x56;
    file_header_vgs[1] =0x67;
    file_header_vgs[2] =0x73;
    file_header_vgs[3] =0x4D;
    file_header_vgs[4] =0x01;
    file_header_vgs[8] =0x01;
    file_header_vgs[12] =0x01;
  }
  fix_vmc_header();
  if(SaveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
bool FF7Save::Export_DEX(const QString &fileName)
{
  if(fileName.isEmpty()){return false;}
  QString prev_type = SG_TYPE;
  if(SG_TYPE != "DEX")
  {
    /* RESET CONTROLS LATER WHEN IMPLIMENTED!!!!!!*/
      setType("DEX");
    //default header..
    file_header_dex[0]=0x31;
    file_header_dex[1]=0x32;
    file_header_dex[2]=0x33;
    file_header_dex[3]=0x2D;
    file_header_dex[4]=0x34;
    file_header_dex[5]=0x35;
    file_header_dex[6]=0x36;
    file_header_dex[7]=0x2D;
    file_header_dex[8]=0x53;
    file_header_dex[9]=0x54;
    file_header_dex[10]=0x44;
    file_header_dex[18]=0x01;
    file_header_dex[20]=0x01;
    file_header_dex[21]=0x4D;
    file_header_dex[22]=0x51;
    for(int i=0x17;i<0x25;i++){file_header_dex[i]=0xA0;}
    file_header_dex[38]=0xFF;
  }
  fix_vmc_header();
  if(SaveFile(fileName))
  {
      setType(prev_type);
      return true;
  }
  else
  {
      setType(prev_type);
      return false;
  }
}
void FF7Save::Import_PSX(int s,const QString &fileName)
{
    if(fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        if((file.size() ==FF7_PSX_SAVE_GAME_SIZE) && ff7file.startsWith(PSX_SAVE_GAME_FILE_ID))
        {
            QByteArray temp; // create a temp to be used when needed
            int index = 0x200;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&slot[s],temp,0x10f4);
            if((fileName.contains("00867")) || (fileName.contains("00869")) || (fileName.contains("00900")) ||
              (fileName.contains("94163")) || (fileName.contains("00700")) || (fileName.contains("01057")) || (fileName.contains("00868")))
            {
                QString string;
                string = fileName.mid(fileName.lastIndexOf("/")+1,fileName.lastIndexOf(".")-1-fileName.lastIndexOf("/"));
                setRegion(s,string.mid(string.lastIndexOf("BA")-1,string.lastIndexOf("FF7-S")+8));
            }
            else {setRegion(s,"");}
         }
         else{return;}
     }
}
void FF7Save::Import_PSV(int s,const QString &fileName)
{
    if(fileName.isEmpty()){return;}
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        if((file.size() ==FF7_PSV_SAVE_GAME_SIZE) && ff7file.startsWith(PSV_SAVE_GAME_FILE_ID))
        {
            int index = 0x284;
            temp = ff7file.mid(index,0x10f4);
            memcpy(&slot[s],temp,0x10f4);
            setRegion(s,QString(ff7file.mid(0x64,19)));
        }//Parse slot data....
        else{return;}
    }
}
void FF7Save::clearslot(int rmslot)
{
    QByteArray temp;
    temp.fill(0x00,0x10f4);
    memcpy(hf[rmslot].sl_header,temp,SG_SLOT_HEADER);// clear the header..
    memcpy(&slot[rmslot],temp,0x10f4);
    memcpy(hf[rmslot].sl_footer,temp,SG_SLOT_FOOTER);// clear the footer..
    SG_Region_String[rmslot].clear();
    if(SG_TYPE =="MC" || SG_TYPE =="PSP" || SG_TYPE =="VGS" || SG_TYPE =="DEX")
    {//clean the mem card header if needed.
        int index = (128+(128*rmslot));
        if (SG_TYPE == "PSP"){index +=0x80;}
        else if (SG_TYPE == "VGS"){index +=0x40;}
        else if (SG_TYPE == "DEX"){index +=0xF40;}
        temp.resize(128);
        temp.fill(0x00);
        temp[0]=0xA0;
        temp[8]=0xFF;
        temp[9]=0xFF;
        temp[0x7F]=0xA0;
        memcpy(&file_headerp[index],temp,128);
    }
}
bool FF7Save::exportChar(int s,int char_num,QString fileName)
{
    if (!fileName.isEmpty())
    {
        FILE *pfile;
        pfile = fopen(fileName.toAscii(),"wb");
        fwrite(&slot[s].chars[char_num],132,1,pfile);
        fclose(pfile);
        return true;
    }
    return false;
}
void FF7Save::importChar(int s,int char_num,QByteArray new_char){memcpy(&slot[s].chars[char_num],new_char.data(),132);}

void FF7Save::fix_sum(const QString &fileName)
{
    void * memory;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite )){return;}
    QDataStream out (&file);
    out.setByteOrder(QDataStream::LittleEndian);
    file.seek(0);//Set pointer to the Beggining
    QByteArray ff7savefile;
    ff7savefile = file.readAll(); //put all data in temp raw file
    memory = (void*) malloc(SG_SIZE);//Memory Allocation
    if (!memory){return;}
    file.seek(0);
    memcpy(memory,ff7savefile.mid(0x00000,SG_SIZE),SG_SIZE);
    //Do checksum foreach slot
    for(int i=0, checksum=0; i<SG_SLOT_NUMBER; i++)
    {
        char * data_pointer = ((char*)memory + SG_HEADER + SG_SLOT_SIZE*i + SG_SLOT_HEADER + 0x04);
        checksum = ff7__checksum(data_pointer); //2 Bytes checksum (a 16-bit Byte checksum)
        if(checksum != 0x4D1D) //if is a blank slot don't write checksum!
        {
            int index = SG_HEADER + SG_SLOT_SIZE*i + SG_SLOT_HEADER;
            file.seek(index);
            out << checksum;
        }
    }
    file.close();
    free(memory);
} 
int FF7Save::ff7__checksum( void* qw )
{
   int i = 0, t, d;
   long r = 0xFFFF, len = 4336;
   long pbit = 0x8000;
   char* b=(char*)qw;

   while( len-- ) {
      t = b[i++];
      r ^= t << 8;
      for(d=0;d<8;d++) {
         if( r & pbit )
            r = ( r << 1 ) ^ 0x1021;
         else
            r <<= 1;
      }
      r &= ( 1 << 16 ) - 1;
   }
   return (r^0xFFFF)&0xFFFF;
}
quint16 FF7Save::itemDecode( quint16 itemraw )
{
    quint16 item;
    int one = 1;
    //Big endian
    //Do Nothing...Item Raw Format QQQQQQQXXXXXXXXX | Item Format QQQQQQQXXXXXXXXX
    if (*(char *)&one){item = itemraw;}
    //Little endian
    //Do things....Item Raw Format XXXXXXXXQQQQQQQX | Item Format XXXXXXXXXQQQQQQQ
    //Do things....Item Raw Format XXXXXXXXQQQQQQQX | Item Format QQQQQQQXXXXXXXXX
    else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
    return item;
}
quint16 FF7Save::itemEncode( quint16 id, quint8 qty )
{
    quint16 item,itemraw;
    int one = 1;
    //Big endian
    //Do Nothing...Item Raw Format QQQQQQQXXXXXXXXX | Item Format QQQQQQQXXXXXXXXX
    if (*(char *)&one) {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    //Little endian
    //Do things....Item Raw Format XXXXXXXXQQQQQQQX | Item Format QQQQQQQXXXXXXXXX
    } else {
        //item = ((itemraw>>(1)%16) & (0x7FFF>>(-1+(1)%16))) | (itemraw<<(16-(1)%16));
        item = ((id << 7) & 0xFF80) | (qty & 0x7F);
        itemraw = (item << 1) | (item >> (16 - 1));
    }
    return itemraw;
}
void FF7Save::setItemId(int s,int item_num,quint16 new_id){slot[s].items[item_num]= itemEncode(new_id,itemQty(s,item_num));}

void FF7Save::setItemQty(int s,int item_num,quint8 new_qty){slot[s].items[item_num]=itemEncode(itemId(s,item_num),new_qty);}

quint16 FF7Save::itemId(int s,int item_num)
{
    quint16 item = itemDecode(slot[s].items[item_num]);
    quint16 id = (item & 0x1FF);
    return id;
}
quint8 FF7Save::itemQty(int s,int item_num)
{
    quint16 item = itemDecode(slot[s].items[item_num]);
    quint8 qty;
    qty = (item & 0xFE00) >> 9;
    return qty;
}

void FF7Save::fix_pc_bytemask(int s)
{
    quint8 mask=0;
    quint8 newheader[0x09] = {0x71,0x73,0x27,0x06,0x00,0x00,0x00,0x00,0x00};
    //calc 0x04 of the header (selected slot) no idea why they choose this way to do it but slot15 = 0xC2 , slot 14= 0xb2  and so on till slot2 = 0x01 and slot 01 0x00
    switch(s)
    {
        case 0: newheader[4]=0x00; break;
        case 1: newheader[4]=0x01; break;
        default:newheader[4]= (16 * (s-2))+2; break;
    };
    //calc 0x05 of the header (slots 1-8 empty?)
    for(int i=0;i<8;i++)
    {
        if(isFF7(i)){mask |= (1<<i);}
    }
    newheader[5]=mask;
    mask=0;// reset for the next byte
    //calc 0x06 of the header (slot 9-15 empty?)
    for(int i=8;i<15;i++)
    {
        if(isFF7(i)){mask |= (1<<(i-8));}
    }
    newheader[6]=mask;
    memcpy(file_headerp,newheader,9);
}
void FF7Save::fix_psx_header(int s)
{   //Time Has to be fixed in the header part of description string.
    if((slot[s].time/3600)>99){hf[s].sl_header[27]=0x58;hf[s].sl_header[29]=0x58;}
    else
    {
        hf[s].sl_header[27] = ((slot[s].time/3600)/10)+0x4F;
        hf[s].sl_header[29] = ((slot[s].time/3600)%10)+0x4F;
    }
    hf[s].sl_header[33] = ((slot[s].time/60%60)/10)+0x4F;
    hf[s].sl_header[35] = ((slot[s].time/60%60)%10)+0x4F;
}
void FF7Save::fix_psv_header(void)
{
 /*do signing stuff*/
 fix_psx_header(0);//adjust time.
}
void FF7Save::fix_vmc_header(void)
{//Set The Index Section Up.
    QByteArray mc_header_2;
    int index=2;

    if(SG_TYPE =="PSP"){for(int i=0; i<0x80; i++){mc_header_2.append(file_header_psp[i]);} index=0x82;}
    if(SG_TYPE =="VGS"){for(int i=0; i<0x40; i++){mc_header_2.append(file_header_vgs[i]);} index=0x42;}
    if(SG_TYPE =="DEX"){for(int i=0; i<0xF40; i++){mc_header_2.append(file_header_dex[i]);} index=0xF42;}
    quint8 xor_byte = 0x00;
    mc_header_2.append("MC");
    if(SG_TYPE =="MC"){for(int k=0; k<125;k++){mc_header_2.append(file_header_mc[k+index]);}}
    if(SG_TYPE =="PSP"){for(int k=0; k<125;k++){mc_header_2.append(file_header_psp[k+index]);}}
    if(SG_TYPE =="VGS"){for(int k=0; k<125;k++){mc_header_2.append(file_header_vgs[k+index]);}}
    if(SG_TYPE =="DEX"){for(int k=0; k<125;k++){mc_header_2.append(file_header_dex[k+index]);}}
    xor_byte= 0x00;
    if(SG_TYPE =="MC"){for(int x=0;x<127;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="PSP"){for(int x=128;x<256;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="VGS"){for(int x=64;x<192;x++){xor_byte^=mc_header_2[x];}}
    if(SG_TYPE =="DEX"){for(int x=0xF40;x<0x1000;x++){xor_byte^=mc_header_2[x];}}
    //write xor byte..
    mc_header_2.append(xor_byte);
    // thats a normal header
    for(int i=0;i<15;i++)
    {
        //calc xor byte..
        index= (128 +(128*i));
        if(SG_TYPE =="PSP"){index+=0x80;}
        if(SG_TYPE =="VGS"){index+=0x40;}
        if(SG_TYPE =="DEX"){index+=0xF40;}
        if(isFF7(i))
        {
           QByteArray temp;
           temp.resize(10);
           temp[0]=0x51;temp[1]=0x00;temp[2]=0x00;temp[3]=0x00;temp[4]=0x00;
           temp[5]=0x20;temp[6]=0x00;temp[7]=0x00;temp[8]=0xFF;temp[9]=0xFF;
           mc_header_2.append(temp);
           mc_header_2.append(region(i));
           temp.resize(98);
           for(int f=0;f<98;f++){temp[f]=0x00;}
           mc_header_2.append(temp);
           xor_byte = 0x00;
           for(int x=0;x<127;x++){xor_byte^=mc_header_2[x+index];}
           mc_header_2.append(xor_byte);

           if(region(i).endsWith("FF7-S01"))
           {for(int P=0;P<512;P++)
               {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S01[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }

           if(region(i).endsWith("FF7-S02"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S02[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S03"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S03[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S04"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S04[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S05"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S05[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S06"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S06[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S07"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S07[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S08"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S08[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S09"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S09[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S10"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S10[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S11"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S11[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S12"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S12[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S13"))
           {for(int P=0;P<512;P++)
                {
                    if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S13[P];}
                    else{hf[i].sl_header[P]= 0x00;}
                }
           }
           if(region(i).endsWith("FF7-S14"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S14[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           if(region(i).endsWith("FF7-S15"))
           {for(int P=0;P<512;P++)
               {
                   if(P<256){hf[i].sl_header[P]= PSX_SAVE_GAME_FILE_HEADER_S15[P];}
                   else{hf[i].sl_header[P]= 0x00;}
               }
           }
           fix_psx_header(i);//fix header in current psx slot
        } // write string if found
        else if(region(i).isEmpty() || region(i).isNull())
        {   //QString empty_header = ;
            mc_header_2.append("\xA0\x00\x00\x00\x00\x00\x00\x00\xFF\xFF",10);
            for (int j=0;j<117;j++){mc_header_2.append('\x00');}
            mc_header_2.append('\xA0');
        }
        else
        {//Write What Ever is in the Header (Non ff7 data)
            if(SG_TYPE =="MC"){for(int j=0;j<128;j++){mc_header_2.append(file_header_mc[index+j]);}}
            if(SG_TYPE =="PSP"){for(int j=0;j<128;j++){mc_header_2.append(file_header_psp[index+j]);}}
            if(SG_TYPE =="VGS"){for(int j=0;j<128;j++){mc_header_2.append(file_header_vgs[index+j]);}}
            if(SG_TYPE =="DEX"){for(int j=0;j<128;j++){mc_header_2.append(file_header_dex[index+j]);}}
        }
    }

    if(SG_TYPE =="MC")
    {
        index=2048;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_mc[index+i]);}// fill the remainder
        memcpy(file_header_mc,mc_header_2,0x2000);
    }
    if(SG_TYPE =="PSP")
    {
        index=2048+0x80;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_psp[index+i]);}// fill the remainder
        memcpy(file_header_psp,mc_header_2,0x2080);
        //PUT PSP CHECKSUMING HERE ..
    }
    if(SG_TYPE =="VGS")
    {
        index=2048+0x40;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_vgs[index+i]);}// fill the remainder
        memcpy(file_header_vgs,mc_header_2,0x2040);
    }
    if(SG_TYPE =="DEX")
    {
        index=2048+0xF40;
        for(int i=0;i<6143;i++){mc_header_2.append(file_header_dex[index+i]);}// fill the remainder
        memcpy(file_header_dex,mc_header_2,0x2F40);
    }
}  

QString FF7Save::region(int s){return SG_Region_String[s];}

void FF7Save::setRegion(int s ,QString new_region)
{
    if( (new_region =="USA") || (new_region == "NTSC-U") || (new_region =="1") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BASCUS-94163FF7-S01"; break;
            case 1: SG_Region_String[s] = "BASCUS-94163FF7-S02"; break;
            case 2: SG_Region_String[s] = "BASCUS-94163FF7-S03"; break;
            case 3: SG_Region_String[s] = "BASCUS-94163FF7-S04"; break;
            case 4: SG_Region_String[s] = "BASCUS-94163FF7-S05"; break;
            case 5: SG_Region_String[s] = "BASCUS-94163FF7-S06"; break;
            case 6: SG_Region_String[s] = "BASCUS-94163FF7-S07"; break;
            case 7: SG_Region_String[s] = "BASCUS-94163FF7-S08"; break;
            case 8: SG_Region_String[s] = "BASCUS-94163FF7-S09"; break;
            case 9: SG_Region_String[s] = "BASCUS-94163FF7-S10"; break;
            case 10: SG_Region_String[s] = "BASCUS-94163FF7-S11"; break;
            case 11: SG_Region_String[s] = "BASCUS-94163FF7-S12"; break;
            case 12: SG_Region_String[s] = "BASCUS-94163FF7-S13"; break;
            case 13: SG_Region_String[s] = "BASCUS-94163FF7-S14"; break;
            case 14: SG_Region_String[s] = "BASCUS-94163FF7-S15"; break;
        }
    }
    else if( (new_region =="UK") || (new_region =="PAL-E") || (new_region =="2") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00867FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00867FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00867FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00867FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00867FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00867FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00867FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00867FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00867FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00867FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00867FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00867FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00867FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00867FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00867FF7-S15"; break;
        }
    }
    else if( (new_region =="French") || (new_region =="PAL-FR") || (new_region =="3") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00868FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00868FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00868FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00868FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00868FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00868FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00868FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00868FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00868FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00868FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00868FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00868FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00868FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00868FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00868FF7-S15"; break;
        }
    }
    else if( (new_region =="German") || (new_region =="PAL-DE") || (new_region =="4") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00869FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00869FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00869FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00869FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00869FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00869FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00869FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00869FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00869FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00869FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00869FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00869FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00869FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00869FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00869FF7-S15"; break;
        }
    }
    else if( (new_region =="Spanish")||(new_region =="PAL-ES")||(new_region == "5") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BESCES-00900FF7-S01"; break;
            case 1: SG_Region_String[s] = "BESCES-00900FF7-S02"; break;
            case 2: SG_Region_String[s] = "BESCES-00900FF7-S03"; break;
            case 3: SG_Region_String[s] = "BESCES-00900FF7-S04"; break;
            case 4: SG_Region_String[s] = "BESCES-00900FF7-S05"; break;
            case 5: SG_Region_String[s] = "BESCES-00900FF7-S06"; break;
            case 6: SG_Region_String[s] = "BESCES-00900FF7-S07"; break;
            case 7: SG_Region_String[s] = "BESCES-00900FF7-S08"; break;
            case 8: SG_Region_String[s] = "BESCES-00900FF7-S09"; break;
            case 9: SG_Region_String[s] = "BESCES-00900FF7-S10"; break;
            case 10:SG_Region_String[s] = "BESCES-00900FF7-S11"; break;
            case 11:SG_Region_String[s] = "BESCES-00900FF7-S12"; break;
            case 12:SG_Region_String[s] = "BESCES-00900FF7-S13"; break;
            case 13:SG_Region_String[s] = "BESCES-00900FF7-S14"; break;
            case 14:SG_Region_String[s] = "BESCES-00900FF7-S15"; break;
        }
    }
    else if( (new_region =="Japanese")||(new_region =="NTSC-J")||(new_region =="6") )
    {
        switch(s)
        {
            case 0: SG_Region_String[s] = "BISLPS-00700FF7-S01"; break;
            case 1: SG_Region_String[s] = "BISLPS-00700FF7-S02"; break;
            case 2: SG_Region_String[s] = "BISLPS-00700FF7-S03"; break;
            case 3: SG_Region_String[s] = "BISLPS-00700FF7-S04"; break;
            case 4: SG_Region_String[s] = "BISLPS-00700FF7-S05"; break;
            case 5: SG_Region_String[s] = "BISLPS-00700FF7-S06"; break;
            case 6: SG_Region_String[s] = "BISLPS-00700FF7-S07"; break;
            case 7: SG_Region_String[s] = "BISLPS-00700FF7-S08"; break;
            case 8: SG_Region_String[s] = "BISLPS-00700FF7-S09"; break;
            case 9: SG_Region_String[s] = "BISLPS-00700FF7-S10"; break;
            case 10:SG_Region_String[s] = "BISLPS-00700FF7-S11"; break;
            case 11:SG_Region_String[s] = "BISLPS-00700FF7-S12"; break;
            case 12:SG_Region_String[s] = "BISLPS-00700FF7-S13"; break;
            case 13:SG_Region_String[s] = "BISLPS-00700FF7-S14"; break;
            case 14:SG_Region_String[s] = "BISLPS-00700FF7-S15"; break;
        }
    }
    else if( (new_region =="International")||(new_region =="NTSC-JI")||(new_region =="7") )
    {
        switch(s)
        {
            case 0:SG_Region_String[s] = "BISLPS-01057FF7-S01"; break;
            case 1:SG_Region_String[s] = "BISLPS-01057FF7-S02"; break;
            case 2:SG_Region_String[s] = "BISLPS-01057FF7-S03"; break;
            case 3:SG_Region_String[s] = "BISLPS-01057FF7-S04"; break;
            case 4:SG_Region_String[s] = "BISLPS-01057FF7-S05"; break;
            case 5:SG_Region_String[s] = "BISLPS-01057FF7-S06"; break;
            case 6:SG_Region_String[s] = "BISLPS-01057FF7-S07"; break;
            case 7:SG_Region_String[s] = "BISLPS-01057FF7-S08"; break;
            case 8:SG_Region_String[s] = "BISLPS-01057FF7-S09"; break;
            case 9:SG_Region_String[s] = "BISLPS-01057FF7-S10"; break;
            case 10:SG_Region_String[s] = "BISLPS-01057FF7-S11"; break;
            case 11:SG_Region_String[s] = "BISLPS-01057FF7-S12"; break;
            case 12:SG_Region_String[s] = "BISLPS-01057FF7-S13"; break;
            case 13:SG_Region_String[s] = "BISLPS-01057FF7-S14"; break;
            case 14:SG_Region_String[s] = "BISLPS-01057FF7-S15"; break;
        }
    }
    else{SG_Region_String[s]=new_region;}
}
void FF7Save::CopySlot(int s){memcpy(&buffer_slot,&slot[s],0x10f4); buffer_region = SG_Region_String[s];}
void FF7Save::PasteSlot(int s)
{
    memcpy(&slot[s],&buffer_slot,0x10f4);
    SG_Region_String[s]= buffer_region;
    SG_Region_String[s].chop(2);
    switch(s)
    {
        case 0: SG_Region_String[s].append("01"); break;
        case 1: SG_Region_String[s].append("02"); break;
        case 2: SG_Region_String[s].append("03"); break;
        case 3: SG_Region_String[s].append("04"); break;
        case 4: SG_Region_String[s].append("05"); break;
        case 5: SG_Region_String[s].append("06"); break;
        case 6: SG_Region_String[s].append("07"); break;
        case 7: SG_Region_String[s].append("08"); break;
        case 8: SG_Region_String[s].append("09"); break;
        case 9: SG_Region_String[s].append("10"); break;
        case 10:SG_Region_String[s].append("11"); break;
        case 11:SG_Region_String[s].append("12"); break;
        case 12:SG_Region_String[s].append("13"); break;
        case 13:SG_Region_String[s].append("14"); break;
        case 14:SG_Region_String[s].append("15"); break;
    }
}

quint8 FF7Save::psx_block_type(int s)
{
    if(type()!="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        return file_headerp[index];
    }
    else{return 0x00;}
}
quint8 FF7Save::psx_block_next(int s)
{
    if(type()!="PC")
    {
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        return file_headerp[index+0x08];
    }
    else{return 0x00;}
}
quint8 FF7Save::psx_block_size(int s)
{
    if(type() !="PC")
    {
        QByteArray temp;
        temp.resize(3);
        int index=128+(128*s);
        if (type() =="PSP"){index+=0x80;}
        else if (type() =="VGS"){index+=0x40;}
        else if (type() =="DEX"){index+=0xF40;}
        else {}
        temp[0]=file_headerp[index+0x04];
        temp[1]=file_headerp[index+0x05];
        temp[2]=file_headerp[index+0x06];
        qint32 value = temp[0] | (temp[1] << 8) | (temp[2] <<16);
        return value/0x2000;
     }
    else{return 0;}
}
bool FF7Save::isFF7(int s)
{
    if(region(s).contains("00867") || region(s).contains("00869") ||
       region(s).contains("00900") || region(s).contains("94163") ||
       region(s).contains("00700") || region(s).contains("01057") ||
       region(s).contains("00868"))
       {return true;}
    else{return false;}
}

bool FF7Save::isPAL(int s)
{
    if(region(s).contains("00867") || region(s).contains("00869") ||
       region(s).contains("00900") || region(s).contains("00868"))
       {return true;}
    else{return false;}
}

bool FF7Save::isNTSC(int s)
{
    if(region(s).contains("00700") || region(s).contains("94163") || region(s).contains("01057"))
       {return true;}
    else{return false;}
}
bool FF7Save::isJPN(int s)
{
    if(region(s).contains("00700") || region(s).contains("01057")){return true;}
    else{return false;}
}
int FF7Save::len_file(void){return SG_SIZE;}
int FF7Save::len_file_header(void){return SG_HEADER;}//Return File Header length
int FF7Save::len_file_footer(void){return SG_FOOTER;}//Return File Footer length
int FF7Save::len_core_save(void){return SG_DATA_SIZE;}//Return Slot length (data portion)
int FF7Save::len_slot_header(void){return SG_SLOT_HEADER;}//Return slot header length
int FF7Save::len_slot_footer(void){return SG_SLOT_FOOTER;}//Return slot footer length
int FF7Save::len_slot(void){return SG_SLOT_SIZE;}//Return Slot length
int FF7Save::number_slots(void){return SG_SLOT_NUMBER;}//Return number of slots in the file_footer_dex
QString FF7Save::type(void){return SG_TYPE;}// Returns the file type loaded.

void FF7Save::setType(QString type)
{//set up all type stuffs...
    if(type == "PC")
    {
        SG_SIZE          = FF7_PC_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_PC_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_PC_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_PC_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_PC_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_PC_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_PC_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_PC_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "PC";
        file_headerp     = file_header_pc;           //pointer to pc file header
        file_footerp     = file_footer_pc;           //pointer to pc file footer
    }
    else if(type =="PSX")
    {
        SG_SIZE          = FF7_PSX_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_PSX_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_PSX_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_PSX_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_PSX_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_PSX_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_PSX_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_PSX_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "PSX";
        file_headerp     = file_header_psx;          //pointer to psx file header
        file_footerp     = file_footer_psx;          //pointer to psx file footer
    }
    else if(type=="MC")
    {
        SG_SIZE          = FF7_MC_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_MC_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_MC_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_MC_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_MC_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_MC_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_MC_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_MC_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "MC";
        file_headerp     = file_header_mc;           //pointer to mc file header
        file_footerp     = file_footer_mc;           //pointer to mc file footer
    }
    else if(type=="PSV")
    {
        SG_SIZE          = FF7_PSV_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_PSV_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_PSV_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_PSV_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_PSV_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_PSV_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_PSV_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_PSV_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "PSV";
        file_headerp     = file_header_psv;          //pointer to psv file header
        file_footerp     = file_footer_psv;          //pointer to psv file footer
    }
    else if(type=="PSP")
    {
        SG_SIZE          = FF7_PSP_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_PSP_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_PSP_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_PSP_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_PSP_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_PSP_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_PSP_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_PSP_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "PSP";
        file_headerp     = file_header_psp;          //pointer to psp file header
        file_footerp     = file_footer_psp;          //pointer to psp file footer
    }
    else if(type=="VGS")
    {
        SG_SIZE          = FF7_VGS_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_VGS_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_VGS_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_VGS_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_VGS_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_VGS_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_VGS_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_VGS_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "VGS";
        file_headerp     = file_header_vgs;          //pointer to vgs file header
        file_footerp     = file_footer_vgs;          //pointer to vgs file footer
    }
    else if(type=="DEX")
    {
        SG_SIZE          = FF7_DEX_SAVE_GAME_SIZE;
        SG_HEADER        = FF7_DEX_SAVE_GAME_HEADER;
        SG_FOOTER        = FF7_DEX_SAVE_GAME_FOOTER;
        SG_DATA_SIZE     = FF7_DEX_SAVE_GAME_DATA_SIZE;
        SG_SLOT_HEADER   = FF7_DEX_SAVE_GAME_SLOT_HEADER;
        SG_SLOT_FOOTER   = FF7_DEX_SAVE_GAME_SLOT_FOOTER;
        SG_SLOT_SIZE     = FF7_DEX_SAVE_GAME_SLOT_SIZE;
        SG_SLOT_NUMBER   = FF7_DEX_SAVE_GAME_SLOT_NUMBER;
        SG_TYPE          = "DEX";
        file_headerp     = file_header_dex;          //pointer to dex file header
        file_footerp     = file_footer_dex;          //pointer to dex file footer
    }
}
void FF7Save::New_Game(int s,QString fileName)
{
    if(fileName.isEmpty() || fileName.isNull())
    {
        memcpy(&slot[s],&default_save,0x10F4);
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&slot[s],temp,0x10f4);
    }
    if(isJPN(s))
    {
        for(int c=0;c<9;c++){setCharName(s,c,"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff");}// clear all names.
        Text.init(1);
        setCharName(s,0,QString::fromUtf8("元ソルジャー"));
        setCharName(s,1,QString::fromUtf8("バレット"));
        setCharName(s,2,QString::fromUtf8("ティファ"));
        setCharName(s,3,QString::fromUtf8("エアリス"));
        setCharName(s,4,QString::fromUtf8("レッド⑬"));
        setCharName(s,5,QString::fromUtf8("ユフィ"));
        setCharName(s,6,QString::fromUtf8(""));
        setCharName(s,7,QString::fromUtf8("セフィロス"));
        setCharName(s,8,QString::fromUtf8("シド"));
    }
    else if(region(s).isEmpty()){setRegion(s,"BASCUS-94163FF7-S01");Text.init(0);}
}

void FF7Save::New_Game_Plus(int s,QString CharFileName,QString fileName)
{
    if(fileName.isEmpty() || fileName.isNull())
    {
        memcpy(&buffer_slot,&default_save,0x10F4);
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){return;}
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index,0x10f4);
        memcpy(&buffer_slot,temp,0x10f4);
    }
    buffer_region = region(s);

    memcpy(&buffer_slot.desc,&slot[s].desc,0x44); // keep a old preview
    memcpy(&buffer_slot.colors,&slot[s].colors,12); // keep old colors.

    for(int i=0;i<9;i++) // keep all old character info.
    {
        if((i==6)||(i==7))// except we have to export cait sith and vincent.the game needs y.cloud/seppie,for the flash back.
        {
            QString outFile;
            if(i==6) //export cait sith. cait sith's stats are only generated when he joins the party.
            {
                    outFile.append(CharFileName);
                    outFile.append("-cait_sith");
                    if(type() != "PSX" || type() != "PSV")
                    {
                        outFile.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        outFile.append(str);
                    }
                }
            else if(i==7)// export vincent. vincent's stats are only generated when he joins the party.
                {
                    outFile.append(CharFileName);
                    outFile.append("-vincent");
                    if(type() != "PSX" || type() != "PSV")
                    {
                        outFile.append("-");
                        QString str;
                        str.setNum(s,10)+1;
                        outFile.append(str);
                    }
                }
            outFile.append(".char");
            exportChar(s,i,outFile);

        }
        else{memcpy(&buffer_slot.chars[i],&slot[s].chars[i],0x84);} // normal character
    }
    memcpy(&buffer_slot.items,&slot[s].items,640);// copy items
    memcpy(&buffer_slot.materias,&slot[s].materias,800); // copy materia
    buffer_slot.gil = slot[s].gil; // copy gil
    buffer_slot.battles = slot[s].battles; // copy battle count
    buffer_slot.runs = slot[s].runs; // copy run count
    buffer_slot.gp = slot[s].gp; // copy gp
    //copy chocobo info.
    buffer_slot.stables = slot[s].stables;
    buffer_slot.stablesoccupied = slot[s].stablesoccupied;
    for(int i=0;i<4;i++){memcpy(&buffer_slot.chocobos[i],&slot[s].chocobos[i],0x10);}
    memcpy(&buffer_slot.chocobonames,slot[s].chocobonames,36);
    memcpy(&buffer_slot.chocostaminas,slot[s].chocostaminas,12);
    for(int i=0;i<2;i++){memcpy(&buffer_slot.choco56,slot[s].choco56,0x10);}
    // copy options
    buffer_slot.battlespeed =slot[s].battlespeed;
    buffer_slot.battlemspeed =slot[s].battlemspeed;
    buffer_slot.options1 = slot[s].options1;
    buffer_slot.options2 = slot[s].options2;
    memcpy(&buffer_slot.controller_map,slot[s].controller_map,16);
    buffer_slot.fieldmspeed = slot[s].fieldmspeed;
    //~~ buffer now ready to be copied~
    slot[s]=buffer_slot;
    setLocation(s,QT_TRANSLATE_NOOP("FF7Save","New Game +"));
}

QByteArray FF7Save::slot_icon(int s)
{
    QByteArray icon;
    if (type() != "PC") //we could have an icon. for all formats except for pc
    {
        for(int i=0;i<0x200;i++){icon.append(hf[s].sl_header[i]);}
    }
    else{icon.fill(0x00,0x200);}//fill with nothing if pc
    return icon;
}
QString FF7Save::charName(int s,int char_num)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<12;n++){text.append(slot[s].chars[char_num].name[n]);}
    return Text.toPC(text);
}
void FF7Save::setCharName(int s,int char_num,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    for (int i=0;i<12;i++){slot[s].chars[char_num].name[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_name);
    memcpy(slot[s].chars[char_num].name,temp,temp.length());
}

QString FF7Save::descName(int s)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<16;n++){text.append(slot[s].desc.name[n]);}
    return Text.toPC(text);
}
void FF7Save::setDescName(int s,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    for (int i=0;i<16;i++){slot[s].desc.name[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_name);
    memcpy(slot[s].desc.name,temp,temp.length());
}

QString FF7Save::location(int s)
{

    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<24;n++){text.append(slot[s].location[n]);}
    return Text.toPC(text);
}
void FF7Save::setLocation(int s, QString new_location)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int i=0;i<24;i++){slot[s].location[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_location);
    memcpy(slot[s].location,temp,temp.length());
    //and the description.
    setDescLocation(s,new_location);
}

QString FF7Save::descLocation(int s)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<24;n++){text.append(slot[s].desc.location[n]);}
    return Text.toPC(text);
}

void FF7Save::setDescLocation(int s, QString new_desc_location)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int i=0;i<32;i++){slot[s].desc.location[i] =0xFF;}
    QByteArray temp = Text.toFF7(new_desc_location);
    memcpy(slot[s].desc.location,temp,temp.length());
}

QString FF7Save::chocoName(int s,int choco_num)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray text;
    for (int n=0;n<6;n++){text.append(slot[s].chocobonames[choco_num][n]);}
    return Text.toPC(text);
}
void FF7Save::setChocoName(int s,int choco_num,QString new_name)
{
    if(isJPN(s)){Text.init(1);}//Japanese
    else{Text.init(0);}// not japanese save.
    QByteArray temp = Text.toFF7(new_name);
    for (int i=0;i<6;i++){slot[s].chocobonames[choco_num][i] =0xFF;}
    memcpy(slot[s].chocobonames[choco_num],temp,temp.length());
}
