//
//  rlib.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

//#include <iostream>
//#include <mach/mach_time.h>
//#include "rng.h"
//#include <Rdefines.h>
//#include <stdio.h>
//#include <R.h>
//
//#include "macro.h"
//#include "eventQ.h"
//#include "population.h"
//
//using namespace std;
//
//Rng * theRng;
//eventQ * theQ;
//
///* Output Pointers */
//extern double * theCARE;
//extern double * theDALY;
//extern double * theCOST;
//extern double * thePOP_15to49;
//extern double * theHIV_15to49;
//extern double * theART_15to49;
//extern double * thePOP_15plus;
//extern double * theAidsDeath_15plus;
//extern double * thePOP_AgeSex_2007;
//extern double * theHIV_AgeSex_2007;
//extern double * thePOP_NoArtCd4_2007;
//extern double * thePOP_AgeSex_2012;
//extern double * theHIV_AgeSex_2012;
//extern double * thePOP_AgeSex_2014;
//extern double * theHIV_AgeSex_2014;
//extern double * theCD4_200;
//extern double * theCD4_200350;
//extern double * theCD4_350500;
//extern double * theCD4_500;
//extern double * theCD4_200_Art;
//extern double * theCD4_200350_Art;
//extern double * theCD4_350500_Art;
//extern double * theCD4_500_Art;
//extern double * theWHO_1;
//extern double * theWHO_2;
//extern double * theWHO_3;
//extern double * theWHO_4;
//extern double * theWHO_1_Art;
//extern double * theWHO_2_Art;
//extern double * theWHO_3_Art;
//extern double * theWHO_4_Art;
//
///* Intervention Pointers */
//int const * p_Hbct;
//int const * p_Vct;
//int const * p_HbctPocCd4;
//int const * p_Linkage;
//int const * p_PreOutreach;
//int const * p_ImprovedCare;
//int const * p_PocCd4;
//int const * p_VctPocCd4;
//int const * p_ArtOutreach;
//int const * p_Adherence;
//int const * p_ImmediateArt;
//int const * p_UniversalTestAndTreat;
//
//extern "C" {
//	
//		/////////////////////
//	
//	SEXP CallCascade(SEXP s_pop,
//					 SEXP s_Hbct,
//					 SEXP s_Vct,
//					 SEXP s_HbctPocCd4,
//					 SEXP s_Linkage,
//					 SEXP s_VctPocCd4,
//					 SEXP s_PreOutreach,
//					 SEXP s_ImprovedCare,
//					 SEXP s_PocCd4,
//					 SEXP s_ArtOutreach,
//					 SEXP s_Adherence,
//					 SEXP s_ImmediateArt,
//					 SEXP s_UniversalTestAndTreat) {
//		
//		PROTECT(s_pop = coerceVector(s_pop, REALSXP));
//		PROTECT(s_Hbct = coerceVector(s_Hbct, INTSXP));
//		PROTECT(s_Vct = coerceVector(s_Vct, INTSXP));
//		PROTECT(s_HbctPocCd4 = coerceVector(s_HbctPocCd4, INTSXP));
//		PROTECT(s_Linkage = coerceVector(s_Linkage, INTSXP));
//		PROTECT(s_VctPocCd4 = coerceVector(s_VctPocCd4, INTSXP));
//		PROTECT(s_PreOutreach = coerceVector(s_PreOutreach, INTSXP));
//		PROTECT(s_ImprovedCare = coerceVector(s_ImprovedCare, INTSXP));
//		PROTECT(s_PocCd4 = coerceVector(s_PocCd4, INTSXP));
//		PROTECT(s_ArtOutreach = coerceVector(s_ArtOutreach, INTSXP));
//		PROTECT(s_Adherence = coerceVector(s_Adherence, INTSXP));
//		PROTECT(s_ImmediateArt = coerceVector(s_ImmediateArt, INTSXP));
//		PROTECT(s_UniversalTestAndTreat = coerceVector(s_UniversalTestAndTreat, INTSXP));
//		
//		/* Assigning Pointers */
//		p_Hbct = INTEGER(s_Hbct);
//		p_Vct = INTEGER(s_Vct);
//		p_HbctPocCd4 = INTEGER(s_HbctPocCd4);
//		p_Linkage = INTEGER(s_Linkage);
//		p_VctPocCd4 = INTEGER(s_VctPocCd4);
//		p_PreOutreach = INTEGER(s_PreOutreach);
//		p_ImprovedCare = INTEGER(s_ImprovedCare);
//		p_PocCd4 = INTEGER(s_PocCd4);
//		p_ArtOutreach = INTEGER(s_ArtOutreach);
//		p_Adherence = INTEGER(s_Adherence);
//		p_ImmediateArt = INTEGER(s_ImmediateArt);
//		p_UniversalTestAndTreat = INTEGER(s_UniversalTestAndTreat);
//		
//		/* THE MODEL */
//		cout << "Hello, Jack - the model is running..." << endl;
//		theRng = new Rng(mach_absolute_time());
//		theQ = new eventQ(0);
//		new population(*REAL(s_pop));
//		theQ->RunEvents();
//		delete theQ;
//		delete theRng;
//		
//		/* OUTPUTS */
//		SEXP sOUT, sCARE, sDALY, sCOST, sPOP_15to49, sHIV_15to49, sART_15to49, sPOP_15plus, sAidsDeath_15plus,
//		sPOP_AgeSex_2007, sHIV_AgeSex_2007, sPOP_NoArtCd4_2007, sPOP_AgeSex_2012, sHIV_AgeSex_2012, sPOP_AgeSex_2014, sHIV_AgeSex_2014,
//		sCD4_200, sCD4_200350, sCD4_350500, sCD4_500, sCD4_200_Art, sCD4_200350_Art, sCD4_350500_Art, sCD4_500_Art,
//		sWHO_1, sWHO_2, sWHO_3, sWHO_4, sWHO_1_Art, sWHO_2_Art, sWHO_3_Art, sWHO_4_Art, sOUTNAMES;
//		
//		PROTECT(sCARE = allocVector(REALSXP,5));
//		PROTECT(sDALY = allocVector(REALSXP,20));
//		PROTECT(sCOST = allocVector(REALSXP,20));
//		PROTECT(sPOP_15to49 = allocVector(REALSXP,60));
//		PROTECT(sHIV_15to49 = allocVector(REALSXP,60));
//		PROTECT(sART_15to49 = allocVector(REALSXP,60));
//		PROTECT(sPOP_15plus = allocVector(REALSXP,60));
//		PROTECT(sAidsDeath_15plus = allocVector(REALSXP,60));
//		PROTECT(sPOP_AgeSex_2007 = allocVector(REALSXP,20));
//		PROTECT(sHIV_AgeSex_2007 = allocVector(REALSXP,20));
//		PROTECT(sPOP_NoArtCd4_2007 = allocVector(REALSXP,4));
//		PROTECT(sPOP_AgeSex_2012 = allocVector(REALSXP,16));
//		PROTECT(sHIV_AgeSex_2012 = allocVector(REALSXP,16));
//		PROTECT(sPOP_AgeSex_2014 = allocVector(REALSXP,10));
//		PROTECT(sHIV_AgeSex_2014 = allocVector(REALSXP,10));
//		PROTECT(sCD4_200 = allocVector(REALSXP,60));
//		PROTECT(sCD4_200350 = allocVector(REALSXP,60));
//		PROTECT(sCD4_350500 = allocVector(REALSXP,60));
//		PROTECT(sCD4_500 = allocVector(REALSXP,60));
//		PROTECT(sCD4_200_Art = allocVector(REALSXP,60));
//		PROTECT(sCD4_200350_Art = allocVector(REALSXP,60));
//		PROTECT(sCD4_350500_Art = allocVector(REALSXP,60));
//		PROTECT(sCD4_500_Art = allocVector(REALSXP,60));
//		PROTECT(sWHO_1 = allocVector(REALSXP,60));
//		PROTECT(sWHO_2 = allocVector(REALSXP,60));
//		PROTECT(sWHO_3 = allocVector(REALSXP,60));
//		PROTECT(sWHO_4 = allocVector(REALSXP,60));
//		PROTECT(sWHO_1_Art = allocVector(REALSXP,60));
//		PROTECT(sWHO_2_Art = allocVector(REALSXP,60));
//		PROTECT(sWHO_3_Art = allocVector(REALSXP,60));
//		PROTECT(sWHO_4_Art = allocVector(REALSXP,60));
//		
//		double * pCARE = REAL(sCARE);
//		double * pDALY = REAL(sDALY);
//		double * pCOST = REAL(sCOST);
//		double * pPOP_15to49 = REAL(sPOP_15to49);
//		double * pHIV_15to49 = REAL(sHIV_15to49);
//		double * pART_15to49 = REAL(sART_15to49);
//		double * pPOP_15plus = REAL(sPOP_15plus);
//		double * pAidsDeath_15plus = REAL(sAidsDeath_15plus);
//		double * pPOP_AgeSex_2007 = REAL(sPOP_AgeSex_2007);
//		double * pHIV_AgeSex_2007 = REAL(sHIV_AgeSex_2007);
//		double * pPOP_NoArtCd4_2007 = REAL(sPOP_NoArtCd4_2007);
//		double * pPOP_AgeSex_2012 = REAL(sPOP_AgeSex_2012);
//		double * pHIV_AgeSex_2012 = REAL(sHIV_AgeSex_2012);
//		double * pPOP_AgeSex_2014 = REAL(sPOP_AgeSex_2014);
//		double * pHIV_AgeSex_2014 = REAL(sHIV_AgeSex_2014);
//		double * pCd4_200 = REAL(sCD4_200);
//		double * pCd4_200350 = REAL(sCD4_200350);
//		double * pCd4_350500 = REAL(sCD4_350500);
//		double * pCd4_500 = REAL(sCD4_500);
//		double * pCd4_200_Art = REAL(sCD4_200_Art);
//		double * pCd4_200350_Art = REAL(sCD4_200350_Art);
//		double * pCd4_350500_Art = REAL(sCD4_350500_Art);
//		double * pCd4_500_Art = REAL(sCD4_500_Art);
//		double * pWHO_1 = REAL(sWHO_1);
//		double * pWHO_2 = REAL(sWHO_2);
//		double * pWHO_3 = REAL(sWHO_3);
//		double * pWHO_4 = REAL(sWHO_4);
//		double * pWHO_1_Art = REAL(sWHO_1_Art);
//		double * pWHO_2_Art = REAL(sWHO_2_Art);
//		double * pWHO_3_Art = REAL(sWHO_3_Art);
//		double * pWHO_4_Art = REAL(sWHO_4_Art);
//		
//		for(size_t i=0;i<60;i++) {
//			if(i<4)
//				pPOP_NoArtCd4_2007[i] = thePOP_NoArtCd4_2007[i];
//			if(i<5)
//				pCARE[i] = theCARE[i];
//			if(i<10) {
//				pPOP_AgeSex_2014[i] = thePOP_AgeSex_2014[i];
//				pHIV_AgeSex_2014[i] = theHIV_AgeSex_2014[i];
//			}
//			if(i<20) {
//				pDALY[i] = theDALY[i];
//				pCOST[i] = theCOST[i];
//				pPOP_AgeSex_2007[i] = thePOP_AgeSex_2007[i];
//				pHIV_AgeSex_2007[i] = theHIV_AgeSex_2007[i];
//			}
//			if(i<16) {
//				pPOP_AgeSex_2012[i] = thePOP_AgeSex_2012[i];
//				pHIV_AgeSex_2012[i] = theHIV_AgeSex_2012[i];
//			}
//			pPOP_15to49[i] = thePOP_15to49[i];
//			pHIV_15to49[i] = theHIV_15to49[i];
//			pART_15to49[i] = theART_15to49[i];
//			pPOP_15plus[i] = thePOP_15plus[i];
//			pAidsDeath_15plus[i] = theAidsDeath_15plus[i];
//			pCd4_200[i] = theCD4_200[i];
//			pCd4_200350[i] = theCD4_200350[i];
//			pCd4_350500[i] = theCD4_350500[i];
//			pCd4_500[i] = theCD4_500[i];
//			pCd4_200_Art[i] = theCD4_200_Art[i];
//			pCd4_200350_Art[i] = theCD4_200350_Art[i];
//			pCd4_350500_Art[i] = theCD4_350500_Art[i];
//			pCd4_500_Art[i] = theCD4_500_Art[i];
//			pWHO_1[i] = theWHO_1[i];
//			pWHO_2[i] = theWHO_2[i];
//			pWHO_3[i] = theWHO_3[i];
//			pWHO_4[i] = theWHO_4[i];
//			pWHO_1_Art[i] = theWHO_1_Art[i];
//			pWHO_2_Art[i] = theWHO_2_Art[i];
//			pWHO_3_Art[i] = theWHO_3_Art[i];
//			pWHO_4_Art[i] = theWHO_4_Art[i];
//		}
//		
//		PROTECT(sOUT = allocVector(VECSXP,31));
//		SET_VECTOR_ELT(sOUT,0,sCARE);
//		SET_VECTOR_ELT(sOUT,1,sDALY);
//		SET_VECTOR_ELT(sOUT,2,sCOST);
//		SET_VECTOR_ELT(sOUT,3,sPOP_15to49);
//		SET_VECTOR_ELT(sOUT,4,sHIV_15to49);
//		SET_VECTOR_ELT(sOUT,5,sART_15to49);
//		SET_VECTOR_ELT(sOUT,6,sPOP_15plus);
//		SET_VECTOR_ELT(sOUT,7,sAidsDeath_15plus);
//		SET_VECTOR_ELT(sOUT,8,sPOP_AgeSex_2007);
//		SET_VECTOR_ELT(sOUT,9,sHIV_AgeSex_2007);
//		SET_VECTOR_ELT(sOUT,10,sPOP_NoArtCd4_2007);
//		SET_VECTOR_ELT(sOUT,11,sPOP_AgeSex_2012);
//		SET_VECTOR_ELT(sOUT,12,sHIV_AgeSex_2012);
//		SET_VECTOR_ELT(sOUT,13,sPOP_AgeSex_2014);
//		SET_VECTOR_ELT(sOUT,14,sHIV_AgeSex_2014);
//		SET_VECTOR_ELT(sOUT,15,sCD4_200);
//		SET_VECTOR_ELT(sOUT,16,sCD4_200350);
//		SET_VECTOR_ELT(sOUT,17,sCD4_350500);
//		SET_VECTOR_ELT(sOUT,18,sCD4_500);
//		SET_VECTOR_ELT(sOUT,19,sCD4_200_Art);
//		SET_VECTOR_ELT(sOUT,20,sCD4_200350_Art);
//		SET_VECTOR_ELT(sOUT,21,sCD4_350500_Art);
//		SET_VECTOR_ELT(sOUT,22,sCD4_500_Art);
//		SET_VECTOR_ELT(sOUT,23,sWHO_1);
//		SET_VECTOR_ELT(sOUT,24,sWHO_2);
//		SET_VECTOR_ELT(sOUT,25,sWHO_3);
//		SET_VECTOR_ELT(sOUT,26,sWHO_4);
//		SET_VECTOR_ELT(sOUT,27,sWHO_1_Art);
//		SET_VECTOR_ELT(sOUT,28,sWHO_2_Art);
//		SET_VECTOR_ELT(sOUT,29,sWHO_3_Art);
//		SET_VECTOR_ELT(sOUT,30,sWHO_4_Art);
//		
//		PROTECT(sOUTNAMES = allocVector(VECSXP,31));
//		SET_VECTOR_ELT(sOUTNAMES,0,mkChar("sCARE"));
//		SET_VECTOR_ELT(sOUTNAMES,1,mkChar("sDALY"));
//		SET_VECTOR_ELT(sOUTNAMES,2,mkChar("sCOST"));
//		SET_VECTOR_ELT(sOUTNAMES,3,mkChar("sPOP_15to49"));
//		SET_VECTOR_ELT(sOUTNAMES,4,mkChar("sHIV_15to49"));
//		SET_VECTOR_ELT(sOUTNAMES,5,mkChar("sART_15to49"));
//		SET_VECTOR_ELT(sOUTNAMES,6,mkChar("sPOP_15plus"));
//		SET_VECTOR_ELT(sOUTNAMES,7,mkChar("sAidsDeath_15plus"));
//		SET_VECTOR_ELT(sOUTNAMES,8,mkChar("sPOP_AgeSex_2007"));
//		SET_VECTOR_ELT(sOUTNAMES,9,mkChar("sHIV_AgeSex_2007"));
//		SET_VECTOR_ELT(sOUTNAMES,10,mkChar("sPOP_NoArtCd4_2007"));
//		SET_VECTOR_ELT(sOUTNAMES,11,mkChar("sPOP_AgeSex_2012"));
//		SET_VECTOR_ELT(sOUTNAMES,12,mkChar("sHIV_AgeSex_2012"));
//		SET_VECTOR_ELT(sOUTNAMES,13,mkChar("sPOP_AgeSex_2014"));
//		SET_VECTOR_ELT(sOUTNAMES,14,mkChar("sHIV_AgeSex_2014"));
//		SET_VECTOR_ELT(sOUTNAMES,15,mkChar("sCD4_200"));
//		SET_VECTOR_ELT(sOUTNAMES,16,mkChar("sCD4_200350"));
//		SET_VECTOR_ELT(sOUTNAMES,17,mkChar("sCD4_350500"));
//		SET_VECTOR_ELT(sOUTNAMES,18,mkChar("sCD4_500"));
//		SET_VECTOR_ELT(sOUTNAMES,19,mkChar("sCD4_200_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,20,mkChar("sCD4_200350_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,21,mkChar("sCD4_350500_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,22,mkChar("sCD4_500_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,23,mkChar("sWHO_1"));
//		SET_VECTOR_ELT(sOUTNAMES,24,mkChar("sWHO_2"));
//		SET_VECTOR_ELT(sOUTNAMES,25,mkChar("sWHO_3"));
//		SET_VECTOR_ELT(sOUTNAMES,26,mkChar("sWHO_4"));
//		SET_VECTOR_ELT(sOUTNAMES,27,mkChar("sWHO_1_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,28,mkChar("sWHO_2_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,29,mkChar("sWHO_3_Art"));
//		SET_VECTOR_ELT(sOUTNAMES,30,mkChar("sWHO_4_Art"));
//		namesgets(sOUT,sOUTNAMES);
//		
//		UNPROTECT(46);
//		return(sOUT);
//	}
//	
//		/////////////////////
//	
//}
