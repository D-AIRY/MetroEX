#pragma once

#include "mycommon.h"
#include "metro/MetroTypes.h"

#include <shlobj_core.h>

#include "RenderPanel.h"
#include "ImagePanel.h"
#include "SoundPanel.h"
#include "DlgModelInfo.h"

class VFXReader;
class MetroTexturesDatabase;
class MetroConfigsDatabase;

namespace MetroEX {
    enum class FileType : size_t {
        Unknown,
        Folder,
        FolderBin,
        Bin,
        BinArchive,
        BinEditable,
        Texture,
        Model,
        Motion,
        Level,
        Sound
    };

    enum class PanelType {
        Texture,
        Model,
        Sound
    };

    struct FileExtractionCtx {
        size_t      fileIdx;
        FileType    type;

        size_t      customOffset;
        size_t      customLength;
        CharString  customFileName;

        // models
        bool        mdlSaveAsObj;
        bool        mdlSaveAsFbx;
        bool        mdlSaveWithAnims;
        // textures
        bool        txUseBC3;
        bool        txSaveAsDds;
        bool        txSaveAsTga;
        bool        txSaveAsPng;
        // sounds
        bool        sndSaveAsOgg;
        bool        sndSaveAsWav;

        // batch
        bool        batch;
        bool        raw;
        size_t      numFilesTotal;
        size_t      progress;
    };

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;


    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm() {
            mImagePanel = nullptr;
            mRenderPanel = nullptr;
            mSoundPanel = nullptr;
            mDlgModelInfo = nullptr;
            mVFXReader = nullptr;

            mExtractionCtx = new FileExtractionCtx;
            mExtractionProgressDlg = nullptr;

            mOriginalRootNode = nullptr;
            mSavedNode = nullptr;

            InitializeComponent();

            this->filterableTreeView->TreeView->ImageList = this->imageListMain;
            this->filterableTreeView->TreeView->NodeMouseClick += (gcnew TreeNodeMouseClickEventHandler(this, &MainForm::filterableTreeView_NodeMouseClick));
            this->filterableTreeView->TreeView->AfterCollapse += (gcnew TreeViewEventHandler(this, &MainForm::filterableTreeView_AfterCollapse));
            this->filterableTreeView->TreeView->AfterExpand += (gcnew TreeViewEventHandler(this, &MainForm::filterableTreeView_AfterExpand));
            this->filterableTreeView->TreeView->AfterSelect += (gcnew TreeViewEventHandler(this, &MainForm::filterableTreeView_AfterSelect));
        }

    protected:
        ~MainForm() {
            if (components) {
                delete components;
            }
        }

    private:
        MetroEX::ImagePanel^        mImagePanel;
        MetroEX::RenderPanel^       mRenderPanel;
        MetroEX::SoundPanel^        mSoundPanel;
        MetroEX::DlgModelInfo^      mDlgModelInfo;

        //
        VFXReader*                  mVFXReader;

        FileExtractionCtx*          mExtractionCtx;
        System::Threading::Thread^  mExtractionThread;
        IProgressDialog*            mExtractionProgressDlg;

        TreeNode^                   mOriginalRootNode;

        MetroTexturesDatabase*      mTexturesDatabase;
        MetroConfigsDatabase*       mConfigsDatabase;

    protected:

    private: System::Windows::Forms::StatusStrip^  statusStrip1;
    private: System::Windows::Forms::SplitContainer^  splitContainer1;




    private: System::Windows::Forms::ImageList^  imageListMain;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel1;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel2;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel3;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel4;
    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportTexture;
    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportModel;
    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportSound;
    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportRaw;
    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportFolder;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsDDSToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsLegacyDDSToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsTGAToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsPNGToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  extractFileToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsOBJToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsFBXToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsOGGToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  saveAsWAVToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  extractFolderToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  extractFolderWithConversionToolStripMenuItem;


    private: System::Windows::Forms::ToolStrip^  toolStrip1;
    private: System::Windows::Forms::ToolStripButton^  toolBtnFileOpen;
    private: System::Windows::Forms::ToolStripButton^  toolBtnAbout;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
    private: System::Windows::Forms::ToolStripButton^  toolBtnImgEnableAlpha;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;





    private: System::Windows::Forms::ContextMenuStrip^  ctxMenuExportBin;
    private: System::Windows::Forms::ToolStripMenuItem^  extractBinRootToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  extractBinChunkToolStripMenuItem;
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
    private: System::Windows::Forms::Panel^  pnlViewers;
    private: System::Windows::Forms::Panel^  pnlMetaProps;
    private: System::Windows::Forms::Panel^  pnlImageProps;
    private: System::Windows::Forms::Label^  lblImgPropMips;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  lblImgPropHeight;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  lblImgPropWidth;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  lblImgPropCompression;

    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Panel^  pnlMdlProps;

    private: System::Windows::Forms::Button^  btnMdlPropPlayStopAnim;
    private: System::Windows::Forms::ListBox^  lstMdlPropMotions;
    private: System::Windows::Forms::Label^  lblMdlPropJoints;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  lblMdlPropTriangles;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  lblMdlPropVertices;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  lblMdlPropType;
    private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::ToolStripButton^  toolBtnCreatePatch;
private: System::Windows::Forms::Button^  btnModelInfo;
private: System::Windows::Forms::ToolStripButton^  toolBtnConvertTexture;

    private: System::Windows::Forms::ToolStripButton^  toolBtnTexturesDatabase;
    private: MetroEXControls::FilterableTreeView^  filterableTreeView;






    private: System::ComponentModel::IContainer^  components;

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>


#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
            this->statusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
            this->filterableTreeView = (gcnew MetroEXControls::FilterableTreeView());
            this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->pnlViewers = (gcnew System::Windows::Forms::Panel());
            this->pnlMetaProps = (gcnew System::Windows::Forms::Panel());
            this->pnlMdlProps = (gcnew System::Windows::Forms::Panel());
            this->btnModelInfo = (gcnew System::Windows::Forms::Button());
            this->btnMdlPropPlayStopAnim = (gcnew System::Windows::Forms::Button());
            this->lstMdlPropMotions = (gcnew System::Windows::Forms::ListBox());
            this->lblMdlPropJoints = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->lblMdlPropTriangles = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->lblMdlPropVertices = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->lblMdlPropType = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->pnlImageProps = (gcnew System::Windows::Forms::Panel());
            this->lblImgPropMips = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->lblImgPropHeight = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->lblImgPropWidth = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->lblImgPropCompression = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->imageListMain = (gcnew System::Windows::Forms::ImageList(this->components));
            this->ctxMenuExportTexture = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->saveAsDDSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveAsLegacyDDSToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveAsTGAToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveAsPNGToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->ctxMenuExportModel = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->saveAsOBJToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveAsFBXToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->ctxMenuExportSound = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->saveAsOGGToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->saveAsWAVToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->ctxMenuExportRaw = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->extractFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->ctxMenuExportFolder = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->extractFolderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->extractFolderWithConversionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
            this->toolBtnFileOpen = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolBtnAbout = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolBtnImgEnableAlpha = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolBtnCreatePatch = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolBtnTexturesDatabase = (gcnew System::Windows::Forms::ToolStripButton());
            this->ctxMenuExportBin = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->extractBinRootToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->extractBinChunkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolBtnConvertTexture = (gcnew System::Windows::Forms::ToolStripButton());
            this->statusStrip1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
            this->splitContainer1->Panel1->SuspendLayout();
            this->splitContainer1->Panel2->SuspendLayout();
            this->splitContainer1->SuspendLayout();
            this->tableLayoutPanel2->SuspendLayout();
            this->pnlMetaProps->SuspendLayout();
            this->pnlMdlProps->SuspendLayout();
            this->pnlImageProps->SuspendLayout();
            this->ctxMenuExportTexture->SuspendLayout();
            this->ctxMenuExportModel->SuspendLayout();
            this->ctxMenuExportSound->SuspendLayout();
            this->ctxMenuExportRaw->SuspendLayout();
            this->ctxMenuExportFolder->SuspendLayout();
            this->toolStrip1->SuspendLayout();
            this->ctxMenuExportBin->SuspendLayout();
            this->SuspendLayout();
            // 
            // statusStrip1
            // 
            this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->statusLabel1, this->statusLabel2,
                    this->statusLabel3, this->statusLabel4
            });
            this->statusStrip1->Location = System::Drawing::Point(0, 697);
            this->statusStrip1->Name = L"statusStrip1";
            this->statusStrip1->Size = System::Drawing::Size(1159, 22);
            this->statusStrip1->TabIndex = 1;
            this->statusStrip1->Text = L"statusStrip1";
            // 
            // statusLabel1
            // 
            this->statusLabel1->Name = L"statusLabel1";
            this->statusLabel1->Size = System::Drawing::Size(286, 17);
            this->statusLabel1->Spring = true;
            this->statusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // statusLabel2
            // 
            this->statusLabel2->Name = L"statusLabel2";
            this->statusLabel2->Size = System::Drawing::Size(286, 17);
            this->statusLabel2->Spring = true;
            this->statusLabel2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // statusLabel3
            // 
            this->statusLabel3->Name = L"statusLabel3";
            this->statusLabel3->Size = System::Drawing::Size(286, 17);
            this->statusLabel3->Spring = true;
            this->statusLabel3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // statusLabel4
            // 
            this->statusLabel4->BorderStyle = System::Windows::Forms::Border3DStyle::Raised;
            this->statusLabel4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->statusLabel4->Name = L"statusLabel4";
            this->statusLabel4->Size = System::Drawing::Size(286, 17);
            this->statusLabel4->Spring = true;
            this->statusLabel4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // splitContainer1
            // 
            this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->splitContainer1->Location = System::Drawing::Point(0, 25);
            this->splitContainer1->Name = L"splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this->splitContainer1->Panel1->Controls->Add(this->filterableTreeView);
            // 
            // splitContainer1.Panel2
            // 
            this->splitContainer1->Panel2->Controls->Add(this->tableLayoutPanel2);
            this->splitContainer1->Size = System::Drawing::Size(1159, 672);
            this->splitContainer1->SplitterDistance = 301;
            this->splitContainer1->TabIndex = 2;
            // 
            // filterableTreeView
            // 
            this->filterableTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
            this->filterableTreeView->FilterTimeout = 1000;
            this->filterableTreeView->Location = System::Drawing::Point(0, 0);
            this->filterableTreeView->Name = L"filterableTreeView";
            this->filterableTreeView->Size = System::Drawing::Size(301, 672);
            this->filterableTreeView->TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this->tableLayoutPanel2->ColumnCount = 1;
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                100)));
            this->tableLayoutPanel2->Controls->Add(this->pnlViewers, 0, 0);
            this->tableLayoutPanel2->Controls->Add(this->pnlMetaProps, 0, 1);
            this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
            this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
            this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
            this->tableLayoutPanel2->RowCount = 2;
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 80)));
            this->tableLayoutPanel2->Size = System::Drawing::Size(854, 672);
            this->tableLayoutPanel2->TabIndex = 0;
            // 
            // pnlViewers
            // 
            this->pnlViewers->Dock = System::Windows::Forms::DockStyle::Fill;
            this->pnlViewers->Location = System::Drawing::Point(0, 0);
            this->pnlViewers->Margin = System::Windows::Forms::Padding(0);
            this->pnlViewers->Name = L"pnlViewers";
            this->pnlViewers->Size = System::Drawing::Size(854, 592);
            this->pnlViewers->TabIndex = 0;
            // 
            // pnlMetaProps
            // 
            this->pnlMetaProps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->pnlMetaProps->Controls->Add(this->pnlMdlProps);
            this->pnlMetaProps->Controls->Add(this->pnlImageProps);
            this->pnlMetaProps->Dock = System::Windows::Forms::DockStyle::Fill;
            this->pnlMetaProps->Location = System::Drawing::Point(0, 592);
            this->pnlMetaProps->Margin = System::Windows::Forms::Padding(0);
            this->pnlMetaProps->Name = L"pnlMetaProps";
            this->pnlMetaProps->Size = System::Drawing::Size(854, 80);
            this->pnlMetaProps->TabIndex = 1;
            // 
            // pnlMdlProps
            // 
            this->pnlMdlProps->Controls->Add(this->btnModelInfo);
            this->pnlMdlProps->Controls->Add(this->btnMdlPropPlayStopAnim);
            this->pnlMdlProps->Controls->Add(this->lstMdlPropMotions);
            this->pnlMdlProps->Controls->Add(this->lblMdlPropJoints);
            this->pnlMdlProps->Controls->Add(this->label9);
            this->pnlMdlProps->Controls->Add(this->lblMdlPropTriangles);
            this->pnlMdlProps->Controls->Add(this->label8);
            this->pnlMdlProps->Controls->Add(this->lblMdlPropVertices);
            this->pnlMdlProps->Controls->Add(this->label7);
            this->pnlMdlProps->Controls->Add(this->lblMdlPropType);
            this->pnlMdlProps->Controls->Add(this->label3);
            this->pnlMdlProps->Location = System::Drawing::Point(3, 2);
            this->pnlMdlProps->Name = L"pnlMdlProps";
            this->pnlMdlProps->Size = System::Drawing::Size(623, 73);
            this->pnlMdlProps->TabIndex = 1;
            // 
            // btnModelInfo
            // 
            this->btnModelInfo->Location = System::Drawing::Point(481, 47);
            this->btnModelInfo->Name = L"btnModelInfo";
            this->btnModelInfo->Size = System::Drawing::Size(75, 23);
            this->btnModelInfo->TabIndex = 10;
            this->btnModelInfo->Text = L"Info";
            this->btnModelInfo->UseVisualStyleBackColor = true;
            this->btnModelInfo->Click += gcnew System::EventHandler(this, &MainForm::btnModelInfo_Click);
            // 
            // btnMdlPropPlayStopAnim
            // 
            this->btnMdlPropPlayStopAnim->Location = System::Drawing::Point(480, 5);
            this->btnMdlPropPlayStopAnim->Name = L"btnMdlPropPlayStopAnim";
            this->btnMdlPropPlayStopAnim->Size = System::Drawing::Size(75, 23);
            this->btnMdlPropPlayStopAnim->TabIndex = 9;
            this->btnMdlPropPlayStopAnim->Text = L"Play";
            this->btnMdlPropPlayStopAnim->UseVisualStyleBackColor = true;
            this->btnMdlPropPlayStopAnim->Click += gcnew System::EventHandler(this, &MainForm::btnMdlPropPlayStopAnim_Click);
            // 
            // lstMdlPropMotions
            // 
            this->lstMdlPropMotions->FormattingEnabled = true;
            this->lstMdlPropMotions->Location = System::Drawing::Point(180, 1);
            this->lstMdlPropMotions->Margin = System::Windows::Forms::Padding(0);
            this->lstMdlPropMotions->Name = L"lstMdlPropMotions";
            this->lstMdlPropMotions->Size = System::Drawing::Size(297, 69);
            this->lstMdlPropMotions->TabIndex = 8;
            this->lstMdlPropMotions->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::lstMdlPropMotions_SelectedIndexChanged);
            // 
            // lblMdlPropJoints
            // 
            this->lblMdlPropJoints->AutoSize = true;
            this->lblMdlPropJoints->Location = System::Drawing::Point(68, 53);
            this->lblMdlPropJoints->Name = L"lblMdlPropJoints";
            this->lblMdlPropJoints->Size = System::Drawing::Size(43, 13);
            this->lblMdlPropJoints->TabIndex = 7;
            this->lblMdlPropJoints->Text = L"100500";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(4, 53);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(37, 13);
            this->label9->TabIndex = 6;
            this->label9->Text = L"Joints:";
            // 
            // lblMdlPropTriangles
            // 
            this->lblMdlPropTriangles->AutoSize = true;
            this->lblMdlPropTriangles->Location = System::Drawing::Point(68, 37);
            this->lblMdlPropTriangles->Name = L"lblMdlPropTriangles";
            this->lblMdlPropTriangles->Size = System::Drawing::Size(43, 13);
            this->lblMdlPropTriangles->TabIndex = 5;
            this->lblMdlPropTriangles->Text = L"100500";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(4, 37);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(53, 13);
            this->label8->TabIndex = 4;
            this->label8->Text = L"Triangles:";
            // 
            // lblMdlPropVertices
            // 
            this->lblMdlPropVertices->AutoSize = true;
            this->lblMdlPropVertices->Location = System::Drawing::Point(68, 21);
            this->lblMdlPropVertices->Name = L"lblMdlPropVertices";
            this->lblMdlPropVertices->Size = System::Drawing::Size(43, 13);
            this->lblMdlPropVertices->TabIndex = 3;
            this->lblMdlPropVertices->Text = L"100500";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(4, 21);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(48, 13);
            this->label7->TabIndex = 2;
            this->label7->Text = L"Vertices:";
            // 
            // lblMdlPropType
            // 
            this->lblMdlPropType->AutoSize = true;
            this->lblMdlPropType->Location = System::Drawing::Point(68, 5);
            this->lblMdlPropType->Name = L"lblMdlPropType";
            this->lblMdlPropType->Size = System::Drawing::Size(51, 13);
            this->lblMdlPropType->TabIndex = 1;
            this->lblMdlPropType->Text = L"Animated";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(4, 5);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(34, 13);
            this->label3->TabIndex = 0;
            this->label3->Text = L"Type:";
            // 
            // pnlImageProps
            // 
            this->pnlImageProps->Controls->Add(this->lblImgPropMips);
            this->pnlImageProps->Controls->Add(this->label5);
            this->pnlImageProps->Controls->Add(this->lblImgPropHeight);
            this->pnlImageProps->Controls->Add(this->label4);
            this->pnlImageProps->Controls->Add(this->lblImgPropWidth);
            this->pnlImageProps->Controls->Add(this->label2);
            this->pnlImageProps->Controls->Add(this->lblImgPropCompression);
            this->pnlImageProps->Controls->Add(this->label1);
            this->pnlImageProps->Location = System::Drawing::Point(721, 3);
            this->pnlImageProps->Name = L"pnlImageProps";
            this->pnlImageProps->Size = System::Drawing::Size(481, 72);
            this->pnlImageProps->TabIndex = 0;
            // 
            // lblImgPropMips
            // 
            this->lblImgPropMips->AutoSize = true;
            this->lblImgPropMips->Location = System::Drawing::Point(81, 52);
            this->lblImgPropMips->Name = L"lblImgPropMips";
            this->lblImgPropMips->Size = System::Drawing::Size(19, 13);
            this->lblImgPropMips->TabIndex = 7;
            this->lblImgPropMips->Text = L"10";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(4, 52);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(32, 13);
            this->label5->TabIndex = 6;
            this->label5->Text = L"Mips:";
            // 
            // lblImgPropHeight
            // 
            this->lblImgPropHeight->AutoSize = true;
            this->lblImgPropHeight->Location = System::Drawing::Point(81, 36);
            this->lblImgPropHeight->Name = L"lblImgPropHeight";
            this->lblImgPropHeight->Size = System::Drawing::Size(31, 13);
            this->lblImgPropHeight->TabIndex = 5;
            this->lblImgPropHeight->Text = L"2048";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(4, 36);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(41, 13);
            this->label4->TabIndex = 4;
            this->label4->Text = L"Height:";
            // 
            // lblImgPropWidth
            // 
            this->lblImgPropWidth->AutoSize = true;
            this->lblImgPropWidth->Location = System::Drawing::Point(81, 20);
            this->lblImgPropWidth->Name = L"lblImgPropWidth";
            this->lblImgPropWidth->Size = System::Drawing::Size(31, 13);
            this->lblImgPropWidth->TabIndex = 3;
            this->lblImgPropWidth->Text = L"2048";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(4, 20);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(38, 13);
            this->label2->TabIndex = 2;
            this->label2->Text = L"Width:";
            // 
            // lblImgPropCompression
            // 
            this->lblImgPropCompression->AutoSize = true;
            this->lblImgPropCompression->Location = System::Drawing::Point(81, 4);
            this->lblImgPropCompression->Name = L"lblImgPropCompression";
            this->lblImgPropCompression->Size = System::Drawing::Size(35, 13);
            this->lblImgPropCompression->TabIndex = 1;
            this->lblImgPropCompression->Text = L"BC6H";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(4, 4);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(70, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Compression:";
            // 
            // imageListMain
            // 
            this->imageListMain->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageListMain.ImageStream")));
            this->imageListMain->TransparentColor = System::Drawing::Color::Transparent;
            this->imageListMain->Images->SetKeyName(0, L"folder_closed.png");
            this->imageListMain->Images->SetKeyName(1, L"folder_opened.png");
            this->imageListMain->Images->SetKeyName(2, L"file_any.png");
            this->imageListMain->Images->SetKeyName(3, L"bin_unkn.png");
            this->imageListMain->Images->SetKeyName(4, L"bin_archive.png");
            this->imageListMain->Images->SetKeyName(5, L"bin_editable.png");
            this->imageListMain->Images->SetKeyName(6, L"image.png");
            this->imageListMain->Images->SetKeyName(7, L"anim.png");
            this->imageListMain->Images->SetKeyName(8, L"sound.png");
            this->imageListMain->Images->SetKeyName(9, L"model.png");
            // 
            // ctxMenuExportTexture
            // 
            this->ctxMenuExportTexture->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->saveAsDDSToolStripMenuItem,
                    this->saveAsLegacyDDSToolStripMenuItem, this->saveAsTGAToolStripMenuItem, this->saveAsPNGToolStripMenuItem
            });
            this->ctxMenuExportTexture->Name = L"ctxMenuExportTexture";
            this->ctxMenuExportTexture->Size = System::Drawing::Size(184, 92);
            // 
            // saveAsDDSToolStripMenuItem
            // 
            this->saveAsDDSToolStripMenuItem->Name = L"saveAsDDSToolStripMenuItem";
            this->saveAsDDSToolStripMenuItem->Size = System::Drawing::Size(183, 22);
            this->saveAsDDSToolStripMenuItem->Text = L"Save as DDS...";
            this->saveAsDDSToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsDDSToolStripMenuItem_Click);
            // 
            // saveAsLegacyDDSToolStripMenuItem
            // 
            this->saveAsLegacyDDSToolStripMenuItem->Name = L"saveAsLegacyDDSToolStripMenuItem";
            this->saveAsLegacyDDSToolStripMenuItem->Size = System::Drawing::Size(183, 22);
            this->saveAsLegacyDDSToolStripMenuItem->Text = L"Save as legacy DDS...";
            this->saveAsLegacyDDSToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsLegacyDDSToolStripMenuItem_Click);
            // 
            // saveAsTGAToolStripMenuItem
            // 
            this->saveAsTGAToolStripMenuItem->Name = L"saveAsTGAToolStripMenuItem";
            this->saveAsTGAToolStripMenuItem->Size = System::Drawing::Size(183, 22);
            this->saveAsTGAToolStripMenuItem->Text = L"Save as TGA...";
            this->saveAsTGAToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsTGAToolStripMenuItem_Click);
            // 
            // saveAsPNGToolStripMenuItem
            // 
            this->saveAsPNGToolStripMenuItem->Name = L"saveAsPNGToolStripMenuItem";
            this->saveAsPNGToolStripMenuItem->Size = System::Drawing::Size(183, 22);
            this->saveAsPNGToolStripMenuItem->Text = L"Save as PNG...";
            this->saveAsPNGToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsPNGToolStripMenuItem_Click);
            // 
            // ctxMenuExportModel
            // 
            this->ctxMenuExportModel->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->saveAsOBJToolStripMenuItem,
                    this->saveAsFBXToolStripMenuItem
            });
            this->ctxMenuExportModel->Name = L"ctxMenuExportModel";
            this->ctxMenuExportModel->Size = System::Drawing::Size(145, 48);
            // 
            // saveAsOBJToolStripMenuItem
            // 
            this->saveAsOBJToolStripMenuItem->Name = L"saveAsOBJToolStripMenuItem";
            this->saveAsOBJToolStripMenuItem->Size = System::Drawing::Size(144, 22);
            this->saveAsOBJToolStripMenuItem->Text = L"Save as OBJ...";
            this->saveAsOBJToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsOBJToolStripMenuItem_Click);
            // 
            // saveAsFBXToolStripMenuItem
            // 
            this->saveAsFBXToolStripMenuItem->Name = L"saveAsFBXToolStripMenuItem";
            this->saveAsFBXToolStripMenuItem->Size = System::Drawing::Size(144, 22);
            this->saveAsFBXToolStripMenuItem->Text = L"Save as FBX...";
            this->saveAsFBXToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsFBXToolStripMenuItem_Click);
            // 
            // ctxMenuExportSound
            // 
            this->ctxMenuExportSound->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->saveAsOGGToolStripMenuItem,
                    this->saveAsWAVToolStripMenuItem
            });
            this->ctxMenuExportSound->Name = L"ctxMenuExportSound";
            this->ctxMenuExportSound->Size = System::Drawing::Size(150, 48);
            // 
            // saveAsOGGToolStripMenuItem
            // 
            this->saveAsOGGToolStripMenuItem->Name = L"saveAsOGGToolStripMenuItem";
            this->saveAsOGGToolStripMenuItem->Size = System::Drawing::Size(149, 22);
            this->saveAsOGGToolStripMenuItem->Text = L"Save as OGG...";
            this->saveAsOGGToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsOGGToolStripMenuItem_Click);
            // 
            // saveAsWAVToolStripMenuItem
            // 
            this->saveAsWAVToolStripMenuItem->Name = L"saveAsWAVToolStripMenuItem";
            this->saveAsWAVToolStripMenuItem->Size = System::Drawing::Size(149, 22);
            this->saveAsWAVToolStripMenuItem->Text = L"Save as WAV...";
            this->saveAsWAVToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsWAVToolStripMenuItem_Click);
            // 
            // ctxMenuExportRaw
            // 
            this->ctxMenuExportRaw->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->extractFileToolStripMenuItem });
            this->ctxMenuExportRaw->Name = L"ctxMenuExportRaw";
            this->ctxMenuExportRaw->Size = System::Drawing::Size(138, 26);
            // 
            // extractFileToolStripMenuItem
            // 
            this->extractFileToolStripMenuItem->Name = L"extractFileToolStripMenuItem";
            this->extractFileToolStripMenuItem->Size = System::Drawing::Size(137, 22);
            this->extractFileToolStripMenuItem->Text = L"Extract file...";
            this->extractFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractFileToolStripMenuItem_Click);
            // 
            // ctxMenuExportFolder
            // 
            this->ctxMenuExportFolder->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->extractFolderToolStripMenuItem,
                    this->extractFolderWithConversionToolStripMenuItem
            });
            this->ctxMenuExportFolder->Name = L"ctxMenuExportFolder";
            this->ctxMenuExportFolder->Size = System::Drawing::Size(240, 48);
            // 
            // extractFolderToolStripMenuItem
            // 
            this->extractFolderToolStripMenuItem->Name = L"extractFolderToolStripMenuItem";
            this->extractFolderToolStripMenuItem->Size = System::Drawing::Size(239, 22);
            this->extractFolderToolStripMenuItem->Text = L"Extract folder...";
            this->extractFolderToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractFolderToolStripMenuItem_Click);
            // 
            // extractFolderWithConversionToolStripMenuItem
            // 
            this->extractFolderWithConversionToolStripMenuItem->Name = L"extractFolderWithConversionToolStripMenuItem";
            this->extractFolderWithConversionToolStripMenuItem->Size = System::Drawing::Size(239, 22);
            this->extractFolderWithConversionToolStripMenuItem->Text = L"Extract folder with conversion...";
            this->extractFolderWithConversionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractFolderWithConversionToolStripMenuItem_Click);
            // 
            // toolStrip1
            // 
            this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
            this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
                this->toolBtnFileOpen,
                    this->toolStripSeparator1, this->toolBtnAbout, this->toolStripSeparator2, this->toolBtnImgEnableAlpha, this->toolBtnCreatePatch,
                    this->toolBtnConvertTexture, this->toolBtnTexturesDatabase
            });
            this->toolStrip1->Location = System::Drawing::Point(0, 0);
            this->toolStrip1->Name = L"toolStrip1";
            this->toolStrip1->Size = System::Drawing::Size(1159, 25);
            this->toolStrip1->TabIndex = 5;
            this->toolStrip1->Text = L"toolStrip1";
            // 
            // toolBtnFileOpen
            // 
            this->toolBtnFileOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolBtnFileOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnFileOpen.Image")));
            this->toolBtnFileOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnFileOpen->Name = L"toolBtnFileOpen";
            this->toolBtnFileOpen->Size = System::Drawing::Size(23, 22);
            this->toolBtnFileOpen->ToolTipText = L"Open Metro Exodus archive...";
            this->toolBtnFileOpen->Click += gcnew System::EventHandler(this, &MainForm::toolBtnFileOpen_Click);
            // 
            // toolStripSeparator1
            // 
            this->toolStripSeparator1->Name = L"toolStripSeparator1";
            this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
            // 
            // toolBtnAbout
            // 
            this->toolBtnAbout->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolBtnAbout->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnAbout.Image")));
            this->toolBtnAbout->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnAbout->Name = L"toolBtnAbout";
            this->toolBtnAbout->Size = System::Drawing::Size(23, 22);
            this->toolBtnAbout->ToolTipText = L"About";
            this->toolBtnAbout->Click += gcnew System::EventHandler(this, &MainForm::toolBtnAbout_Click);
            // 
            // toolStripSeparator2
            // 
            this->toolStripSeparator2->Name = L"toolStripSeparator2";
            this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
            // 
            // toolBtnImgEnableAlpha
            // 
            this->toolBtnImgEnableAlpha->Checked = true;
            this->toolBtnImgEnableAlpha->CheckState = System::Windows::Forms::CheckState::Checked;
            this->toolBtnImgEnableAlpha->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->toolBtnImgEnableAlpha->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
            this->toolBtnImgEnableAlpha->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnImgEnableAlpha.Image")));
            this->toolBtnImgEnableAlpha->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnImgEnableAlpha->Name = L"toolBtnImgEnableAlpha";
            this->toolBtnImgEnableAlpha->Size = System::Drawing::Size(23, 22);
            this->toolBtnImgEnableAlpha->Text = L"A";
            this->toolBtnImgEnableAlpha->ToolTipText = L"Enable alpha";
            this->toolBtnImgEnableAlpha->Click += gcnew System::EventHandler(this, &MainForm::toolBtnImgEnableAlpha_Click);
            // 
            // toolBtnCreatePatch
            // 
            this->toolBtnCreatePatch->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolBtnCreatePatch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnCreatePatch.Image")));
            this->toolBtnCreatePatch->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnCreatePatch->Name = L"toolBtnCreatePatch";
            this->toolBtnCreatePatch->Size = System::Drawing::Size(23, 22);
            this->toolBtnCreatePatch->Text = L"Create patch";
            this->toolBtnCreatePatch->Click += gcnew System::EventHandler(this, &MainForm::toolBtnCreatePatch_Click);
            // 
            // toolBtnTexturesDatabase
            // 
            this->toolBtnTexturesDatabase->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolBtnTexturesDatabase->Enabled = false;
            this->toolBtnTexturesDatabase->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnTexturesDatabase.Image")));
            this->toolBtnTexturesDatabase->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnTexturesDatabase->Name = L"toolBtnTexturesDatabase";
            this->toolBtnTexturesDatabase->Size = System::Drawing::Size(23, 22);
            this->toolBtnTexturesDatabase->Text = L"toolStripButton1";
            this->toolBtnTexturesDatabase->ToolTipText = L"Textures Database Viewer";
            this->toolBtnTexturesDatabase->Click += gcnew System::EventHandler(this, &MainForm::toolBtnTexturesDatabase_Click);
            // 
            // ctxMenuExportBin
            // 
            this->ctxMenuExportBin->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->extractBinRootToolStripMenuItem,
                    this->extractBinChunkToolStripMenuItem
            });
            this->ctxMenuExportBin->Name = L"ctxMenuExportBin";
            this->ctxMenuExportBin->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
            this->ctxMenuExportBin->Size = System::Drawing::Size(163, 48);
            // 
            // extractBinRootToolStripMenuItem
            // 
            this->extractBinRootToolStripMenuItem->Name = L"extractBinRootToolStripMenuItem";
            this->extractBinRootToolStripMenuItem->Size = System::Drawing::Size(162, 22);
            this->extractBinRootToolStripMenuItem->Text = L"Extract root file...";
            this->extractBinRootToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractBinRootToolStripMenuItem_Click);
            // 
            // extractBinChunkToolStripMenuItem
            // 
            this->extractBinChunkToolStripMenuItem->Name = L"extractBinChunkToolStripMenuItem";
            this->extractBinChunkToolStripMenuItem->Size = System::Drawing::Size(162, 22);
            this->extractBinChunkToolStripMenuItem->Text = L"Extract this file...";
            this->extractBinChunkToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractBinChunkToolStripMenuItem_Click);
            // 
            // toolBtnConvertTexture
            // 
            this->toolBtnConvertTexture->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolBtnConvertTexture->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolBtnConvertTexture.Image")));
            this->toolBtnConvertTexture->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolBtnConvertTexture->Name = L"toolBtnConvertTexture";
            this->toolBtnConvertTexture->Size = System::Drawing::Size(23, 22);
            this->toolBtnConvertTexture->ToolTipText = L"Convert texture to Metro format";
            this->toolBtnConvertTexture->Click += gcnew System::EventHandler(this, &MainForm::toolBtnConvertTexture_Click);
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1159, 719);
            this->Controls->Add(this->splitContainer1);
            this->Controls->Add(this->toolStrip1);
            this->Controls->Add(this->statusStrip1);
            this->Name = L"MainForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"MetroEX - \"Metro Exodus\" files explorer";
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            this->statusStrip1->ResumeLayout(false);
            this->statusStrip1->PerformLayout();
            this->splitContainer1->Panel1->ResumeLayout(false);
            this->splitContainer1->Panel2->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
            this->splitContainer1->ResumeLayout(false);
            this->tableLayoutPanel2->ResumeLayout(false);
            this->pnlMetaProps->ResumeLayout(false);
            this->pnlMdlProps->ResumeLayout(false);
            this->pnlMdlProps->PerformLayout();
            this->pnlImageProps->ResumeLayout(false);
            this->pnlImageProps->PerformLayout();
            this->ctxMenuExportTexture->ResumeLayout(false);
            this->ctxMenuExportModel->ResumeLayout(false);
            this->ctxMenuExportSound->ResumeLayout(false);
            this->ctxMenuExportRaw->ResumeLayout(false);
            this->ctxMenuExportFolder->ResumeLayout(false);
            this->toolStrip1->ResumeLayout(false);
            this->toolStrip1->PerformLayout();
            this->ctxMenuExportBin->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
        // toolstrip buttons
        void toolBtnFileOpen_Click(System::Object^ sender, System::EventArgs^ e);
        void toolBtnAbout_Click(System::Object^ sender, System::EventArgs^ e);
        void toolBtnImgEnableAlpha_Click(System::Object^  sender, System::EventArgs^ e);
        // treeview
        void filterableTreeView_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
        void filterableTreeView_AfterCollapse(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
        void filterableTreeView_AfterExpand(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
        void filterableTreeView_NodeMouseClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e);
        // context menu
        void extractFileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsDDSToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsLegacyDDSToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsTGAToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsPNGToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsOBJToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsFBXToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsOGGToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void saveAsWAVToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void extractBinRootToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void extractBinChunkToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

        void extractFolderToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
        void extractFolderWithConversionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

    public:
        void ShowErrorMessage(String^ message);
        //
    private:
        void UpdateFilesList();
        void AddFoldersRecursive(const MetroFile& dir, const size_t folderIdx, TreeNode^ rootItem, const size_t configBinIdx);
        void AddBinaryArchive(const MetroFile& mf, const size_t fileIdx, TreeNode^ rootItem);
        void DetectFileAndShow(const size_t fileIdx);
        void ShowTexture(const size_t fileIdx);
        void ShowModel(const size_t fileIdx);
        void ShowSound(const size_t fileIdx);
        void SwitchViewPanel(PanelType t);
        void SwitchInfoPanel(PanelType t);

        // extraction
        CharString MakeFileOutputName(const MetroFile& mf, const FileExtractionCtx& ctx);
        void TextureSaveHelper(const fs::path& folderPath, const FileExtractionCtx& ctx, const CharString& name);
        bool ExtractFile(const FileExtractionCtx& ctx, const fs::path& outPath);
        bool ExtractTexture(const FileExtractionCtx& ctx, const fs::path& outPath);
        bool ExtractModel(const FileExtractionCtx& ctx, const fs::path& outPath);
        bool ExtractSound(const FileExtractionCtx& ctx, const fs::path& outPath);
        bool ExtractFolderComplete(const FileExtractionCtx& ctx, const fs::path& outPath);
        void ExtractionProcessFunc(Object^ folderPath);

        // property panels
        // model props
        void lstMdlPropMotions_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
        void btnMdlPropPlayStopAnim_Click(System::Object^ sender, System::EventArgs^ e);
        void btnModelInfo_Click(System::Object^ sender, System::EventArgs^ e);
        void OnDlgModelInfo_Closed(System::Object^ sender, System::EventArgs^ e);

        // patch creation
        void toolBtnCreatePatch_Click(System::Object^ sender, System::EventArgs^ e);
        void toolBtnConvertTexture_Click(System::Object^ sender, System::EventArgs^ e);

        // textures database
        void toolBtnTexturesDatabase_Click(System::Object^ sender, System::EventArgs^ e);
        TreeNode^ FindNode(TreeNode^ parent, String^ text);
        TreeNode^ mSavedNode;

    public:
        void ResetTreeView();
        bool FindAndSelect(String^ text, array<String^>^ extensions);
    };
}
