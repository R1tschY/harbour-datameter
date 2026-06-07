Name:       harbour-datameter
Summary:    Check mobile data usage
Version:    0.2.0
Release:    0
Group:      Qt/Qt
License:    GPLv3
URL:        https://github.com/R1tschY/harbour-datameter
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-datameter.yaml
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  desktop-file-utils

%description
Sailfish OS application to retrieve mobile data usage from your mobile network provider.


%prep
%setup -q -n %{name}-%{version}


%build
%qmake5 
make %{?_smp_mflags}


%install
rm -rf %{buildroot}
%qmake5_install

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop


%files
%defattr(-,root,root,-)
%{_bindir}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png