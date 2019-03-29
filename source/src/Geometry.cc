#include "Geometry.hh"
#include "G4Orb.hh"
#include "G4Box.hh"
#include "G4Trd.hh"/////
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4PVReplica.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"

Geometry::Geometry() {}
Geometry::~Geometry() {}

G4VPhysicalVolume* Geometry::Construct()
{
// Get pointer to 'Material Manager'
G4NistManager* materi_Man = G4NistManager::Instance();

// Define 'World Volume'
G4Orb* World = new G4Orb("World",30*m/2);
 
G4Material* Vacuum = new G4Material("Intergalactic", 1, 1.008*g/mole, 1.e-25*g/cm3,kStateGas, 2.73*kelvin, 3.e-18*pascal);
G4LogicalVolume* World_LV = new G4LogicalVolume(World, Vacuum, "World_LV");
World_LV->SetVisAttributes (G4VisAttributes::Invisible);
G4int World_ID=0;    
G4PVPlacement* World_PV = new G4PVPlacement(G4Transform3D(), "World_PV", World_LV, 0, false, World_ID);

// Define Shield

//CFRP
G4Box* sheild_0= new G4Box( "sheild_0", 40*mm/2, 40*mm/2, 5*mm/2);
  G4Material* sheild_0_M = new G4Material("CFRP",  1.66*g/cm3, 1);
  sheild_0_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_C"),1);
G4LogicalVolume* sheild_0_LV = new G4LogicalVolume( sheild_0, sheild_0_M, "sheild_0_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, -11.22*mm), "sheild_0_PV", sheild_0_LV, World_PV, false, 0);

//Glass epoxy(2FR-4)
G4Box* sheild_1= new G4Box( "sheild_1", 40*mm/2, 40*mm/2, 3.15*mm/2);
    G4Material* sheild_1_M = new G4Material("FR4",1.700*g/cm3,5);
    sheild_1_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_Si") , 0.18077359);
    sheild_1_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_O")  , 0.4056325);
    sheild_1_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_C")  , 0.27804208);
    sheild_1_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_H")  , 0.068442752);
    sheild_1_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_Br") , 0.067109079);
G4LogicalVolume* sheild_1_LV = new G4LogicalVolume( sheild_1, sheild_1_M, "sheild_1_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, -6.145*mm), "sheild_1_PV", sheild_1_LV, World_PV, false, 1);

//Al
G4Box* sheild_2= new G4Box( "sheild_2", 40*mm/2, 40*mm/2, 0.3*mm/2);
G4Material* sheild_2_M = materi_Man->FindOrBuildMaterial("G4_Al");
G4LogicalVolume* sheild_2_LV = new G4LogicalVolume( sheild_2, sheild_2_M, "sheild_2_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, -3.42*mm), "sheild_2_PV", sheild_2_LV, World_PV, false, 2);

//Copper
G4Box* sheild_3= new G4Box( "sheild_3", 40*mm/2, 40*mm/2, 0.07*mm/2);
G4Material* sheild_3_M = materi_Man->FindOrBuildMaterial("G4_Cu");
G4LogicalVolume* sheild_3_LV = new G4LogicalVolume( sheild_3, sheild_3_M, "sheild_3_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, -2.235*mm), "sheild_3_PV", sheild_3_LV, World_PV, false, 3);

//Plastic
G4Box* sheild_4= new G4Box( "sheild_4", 40*mm/2, 40*mm/2, 0.2*mm/2);
  G4Material* sheild_4_M = new G4Material ("Polypropelene" , 0.91*g/cm3, 2);
  sheild_4_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_H"),0.6666666666667);
  sheild_4_M->AddMaterial(materi_Man->FindOrBuildMaterial("G4_C"),0.3333333333333);
G4LogicalVolume* sheild_4_LV = new G4LogicalVolume( sheild_4, sheild_4_M, "sheild_4_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, -1.1*mm), "sheild_4_PV", sheild_4_LV, World_PV, false, 4);

//Si Detector
G4Box* SiDetector = new G4Box( "SiDetector", 20*mm/2, 20*mm/2, 0.3*mm/2);
G4Material* SiDetector_M = materi_Man->FindOrBuildMaterial("G4_Si");
G4LogicalVolume* SiDetector_LV = new G4LogicalVolume( SiDetector, SiDetector_M, "SiDetector_LV", 0, 0, 0 );
new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, 0.15*mm), "SiDetector_PV", SiDetector_LV, World_PV, false, 1000);


/////////////////////////////////////////////////
//  Detector assembly/////////////////////////////////////////////////////////////////////////////////////

// Define 'Aluminum window'
// Define the shape of solid
  //  G4Tubs* AlWindow = new G4Tubs("AlWindow", 0*mm/2, 61*mm/2, 0.3*mm/2,0,360*deg);
  //  G4Material* AlWindow_M = materi_Man->FindOrBuildMaterial("G4_Al");
  //  G4LogicalVolume* AlWindow_LV = new G4LogicalVolume( AlWindow, AlWindow_M, "AlWindow_LV", 0, 0, 0 );
  //  new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, 5.5*mm), "AlWindow_PV", AlWindow_LV, World_PV, false, 90); 

   
// Define '1st Pixcel Detector' - Global Envelop
  //  // Define the shape of the global envelop
  //  G4Tubs* SiDetector = new G4Tubs("SiDetector", 0*mm/2, 40*mm/2, 1.5*mm/2,0,360*deg);
  //  G4Material* SiDetector_M = materi_Man->FindOrBuildMaterial("G4_Si");
  //  G4LogicalVolume* SiDetector_LV = new G4LogicalVolume(SiDetector, SiDetector_M, "SiDetector_LV");
   
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,10);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+2.2*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,20);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+4.4*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,30);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+6.6*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,40);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+8.8*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,50);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+11*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,60);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+13.2*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,70);
  //  new G4PVPlacement(0,G4ThreeVector(0*mm,0*mm,7.7+1.5/2+15.4*mm), "SiDetector_PV", SiDetector_LV, World_PV,false,80);

/*   
// Define '2st Pixcel Detector' - Global Envelop
   G4Box* SiDetector_2 = new G4Box("SiDetector_2", 3.53*mm/2, 23.04*mm/2, 0.6*mm/2);
   G4Material* SiDetector_M_2 = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* SiDetector_LV_2 = new G4LogicalVolume(SiDetector_2, SiDetector_M_2, "SiDetector_LV_2");
   SiDetector_LV_2->SetVisAttributes (G4VisAttributes::Invisible);
   
   G4int PixelNo_2 = 64;                                
   G4Box* SiPixel_2 = new G4Box("SiPixel_2", 3.53*mm/2, 23.04*mm/PixelNo_2/2, 0.6*mm/2);
   G4Material* SiPixel_M_2 = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* SiPixel_LV_2 = new G4LogicalVolume(SiPixel_2, SiPixel_M_2, "SiPixel_LV_2");
   new G4PVReplica("SiPixel_PV_2", SiPixel_LV_2, SiDetector_LV_2, kYAxis, PixelNo_2, 23.04*mm/PixelNo_2);

   new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, 10.92*mm), "SiDetector_PV_#1", SiDetector_LV_2, World_PV, false,300);

////////////////////////////////////////////////////////////////
   new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, 12.72*mm), "SiDetector_PV_#2", SiDetector_LV_2, World_PV, false, 4000);
  
////////////////////////////////////////////////////////////////
   new G4PVPlacement(0,G4ThreeVector(0*mm, 0*mm, 14.52*mm), "SiDetector_PV_#2", SiDetector_LV_2, World_PV, false, 5000);
 */ 

return World_PV;
}
