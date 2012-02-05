
/*
 *  fingerDetector.cpp
 *  openFrameworks
 *
 *  Created by Dani Quilez on 3/30/09.
 *  Copyright 2009 Mechanics_of_destruction. All rights reserved.
 *
 */

#include "fingerDetector.h"

fingerDetector::fingerDetector()
{
   //k is used for fingers and smk is used for hand detection
   k=35;
   smk=200;
   teta=0.f;
}
bool fingerDetector::findFingers (ofxCvBlob blob)
{
   ppico.clear();
   kpointcurv.clear();

   for(int i=k; i<blob.nPts-k; i++)
   {

      //calculating angre between vectors
      v1.set(blob.pts.x-blob.pts[i-k].x,blob.pts.y-blob.pts[i-k].y);
      v2.set(blob.pts.x-blob.pts[i+k].x,blob.pts.y-blob.pts[i+k].y);

      v1D.set(blob.pts.x-blob.pts[i-k].x,blob.pts.y-blob.pts[i-k].y,0);
      v2D.set(blob.pts.x-blob.pts[i+k].x,blob.pts.y-blob.pts[i+k].y,0);

      vxv = v1D.cross(v2D);

      v1.normalize();
      v2.normalize();
      teta=v1.angle(v2);

      //control conditions
      if(fabs(teta) < 40)
      {   //pik?
         if(vxv.z > 0)
         {
            bfingerRuns.push_back(true);
            //we put the select poins into ppico vector
            ppico.push_back(blob.pts);
            kpointcurv.push_back(teta);
         }
      }
   }
   if(ppico.size()>0)
   {
      return true;
   }
   else
   {
      return false;
   }

}
void fingerDetector::findHands(ofxCvBlob smblob)
{
   smppico.clear();
   smkpointcurv.clear();
   lhand.clear();
   rhand.clear();

   hcentroid=smblob.centroid;

   for(int i=smk; i<smblob.nPts-smk; i++)
   {

      v1.set(smblob.pts.x-smblob.pts[i-smk].x,smblob.pts.y-smblob.pts[i-smk].y);
      v2.set(smblob.pts.x-smblob.pts[i+smk].x,smblob.pts.y-smblob.pts[i+smk].y);

      v1D.set(smblob.pts.x-smblob.pts[i-smk].x,smblob.pts.y-smblob.pts[i-smk].y,0);
      v2D.set(smblob.pts.x-smblob.pts[i+smk].x,smblob.pts.y-smblob.pts[i+smk].y,0);

      vxv = v1D.cross(v2D);

      v1.normalize();
      v2.normalize();

      teta=v1.angle(v2);

      if(fabs(teta) < 30)
      {   //pik?
         if(vxv.z > 0)
         {
            smppico.push_back(smblob.pts);
            smkpointcurv.push_back(teta);
         }
      }
   }
   lhand.push_back(smppico[0]);
   for(int i=1; i<smppico.size();i++)
   {
      aux1.set(smppico.x-smppico[0].x,smppico.y-smppico[0].y);
      dlh=aux1.length();

      //we detect left and right hand and

      if(dlh<100)
      {
         lhand.push_back(smppico);
      }
      if(dlh>100)
      {
         rhand.push_back(smppico);
      }
   }
   //try to find for each hand the point wich is farder to the centroid of the Blob
   aux1.set(lhand[0].x-hcentroid.x,lhand[0].y-hcentroid.y);
   lhd=aux1.length();
   max=lhd;
   handspos[0]=0;
   for(int i=1; i<lhand.size(); i++)
   {
      aux1.set(lhand.x-hcentroid.x,lhand.y-hcentroid.y);
      lhd=aux1.length();
      if(lhd>max)
      {
         max=lhd;
         handspos[0]=i;
      }
   }
   aux1.set(rhand[0].x-hcentroid.x,rhand[0].y-hcentroid.y);
   lhd=aux1.length();
   max=lhd;
   handspos[1]=0;
   for(int i=1; i<rhand.size(); i++)
   {
      aux1.set(rhand.x-hcentroid.x,rhand.y-hcentroid.y);
      lhd=aux1.length();
      if(lhd>max)
      {
         max=lhd;
         handspos[1]=i;
      }
   }
   //Positions of hands are in (lhand[handspos[0]].x, y+lhand[handspos[0]].y) for left hand and (rhand[handspos[1]].x, y+rhand[handspos[1]].y) for right hand

}
void fingerDetector::draw(float x, float y)
{
   for(int i=0; i<ppico.size(); i++)
   {
      ofEnableAlphaBlending();
      ofFill();
       ofSetColor(255,0,0,20);
       ofCircle(x+ppico.x, y+ppico.y, 10);
   }
}
void fingerDetector::drawhands(float x, float y)
{
   ofFill();
   ofSetColor(255,255,0);
   ofCircle(x+lhand[handspos[0]].x, y+lhand[handspos[0]].y, 50);
   ofSetColor(255,0,0);
   ofCircle(x+rhand[handspos[1]].x, y+rhand[handspos[1]].y, 50);

}
