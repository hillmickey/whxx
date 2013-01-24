#include "stdafx.h"
#include "ximage.h"
#include "StandardImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GRAY_IMAGE 0
#define COLOR_IMAGE 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NStandardImage::NStandardImage()
{
	m_pImage   = NULL;
	m_FileType = 0;
	m_nFrames  = 1;
	m_nFrameNb = 0;
}

NStandardImage::~NStandardImage()
{
	Release();
}

LPVOID NStandardImage::GetBits()
{
	ASSERT(m_pImage);
	return m_pImage->GetBits();
}

BOOL NStandardImage::Create(UINT nWidth, UINT nHeight, UINT nBPP)
{
	if(!m_pImage)
		m_pImage = new CxImage;
	m_pImage->Create(nWidth, nHeight, nBPP);
	return TRUE;
}

BOOL NStandardImage::Load(LPCTSTR lpszFile)
{
	if(!m_pImage)
		m_pImage = new CxImage;
	
	ASSERT(m_pImage);
	
	CString filename(lpszFile);
	int nIndex = filename.ReverseFind('.');
	
	CString ext = filename.Right(filename.GetLength()-nIndex-1);
	ext.MakeLower();
	if(ext == "")
		return FALSE;

	if(ext == "bmp")						m_FileType = CXIMAGE_FORMAT_BMP;
	else if(ext == "gif")					m_FileType = CXIMAGE_FORMAT_GIF;
	else if(ext == "jpg"||ext == "jpeg")	m_FileType = CXIMAGE_FORMAT_JPG;
	else if(ext == "png")					m_FileType = CXIMAGE_FORMAT_PNG;
	else if(ext == "ico")					m_FileType = CXIMAGE_FORMAT_ICO;
	else if(ext == "tiff"||ext == "tif")	m_FileType = CXIMAGE_FORMAT_TIF;
	else if(ext == "tga")					m_FileType = CXIMAGE_FORMAT_TGA;
	else if(ext == "pcx")					m_FileType = CXIMAGE_FORMAT_PCX;
	else								return FALSE;

	return m_pImage->ReadFile(lpszFile, m_FileType);
}

BOOL NStandardImage::Rendering(LPVOID pBuffer, RENDERINGOPTION *pRO)
{
	ASSERT(pBuffer);
	ASSERT(pRO);
	
	int nSize = m_pImage->GetSize();
	pRO->nBPP = m_pImage->GetBpp();

	int nHeaderSize = sizeof(BITMAPINFO);
	
	int nBPP = pRO->nBPP;
	if(nBPP<=8)
	{
		nHeaderSize += ((1<<nBPP)-1) * sizeof(RGBQUAD);
	}

	if(m_pImage->pDib == NULL)
		return FALSE;

	memcpy(pRO->pBMPInfo, m_pImage->pDib, nHeaderSize);
	memcpy(pBuffer, m_pImage->GetBits(), nSize);

	return TRUE;
}

void NStandardImage::Release()
{
	if(m_pImage)
		delete m_pImage;
	m_pImage = NULL;
}


UINT NStandardImage::GetBPP() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetBpp();
}

UINT NStandardImage::GetWidth() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetWidth();
}

UINT NStandardImage::GetHeight() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetHeight();
}

UINT NStandardImage::GetSize() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetSize();
}

LPRGBQUAD NStandardImage::GetPalette() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetPalette();
}

void NStandardImage::SetPalette(LPRGBQUAD pPal,DWORD nColors) 
{
	ASSERT(m_pImage); 
	m_pImage->SetPalette(pPal, nColors);
}
 
UINT NStandardImage::GetPaletteSize() 
{
	ASSERT(m_pImage); 
	return m_pImage->GetPaletteSize();
}

BOOL NStandardImage::IsValid() 
{
	ASSERT(m_pImage); 
	return m_pImage->IsValid();
}


BOOL NStandardImage::CoarseRendering(LPVOID pBuffer, LPRENDEROPTION pRO)
{
	return Rendering(pBuffer, pRO);
}

int NStandardImage::GetImageType()
{
	return COLOR_IMAGE;
}

